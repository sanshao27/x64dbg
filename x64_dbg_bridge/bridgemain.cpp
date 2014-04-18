#include "_global.h"
#include "bridgemain.h"
#include <stdio.h>
#include <new>

static HINSTANCE hInst;
static char szIniFile[1024]="";

#ifdef _WIN64
#define dbg_lib "x64_dbg.dll"
#define gui_lib "x64_gui.dll"
#else
#define dbg_lib "x32_dbg.dll"
#define gui_lib "x32_gui.dll"
#endif // _WIN64

//Bridge
BRIDGE_IMPEXP const char* BridgeInit()
{
    ///Settings load
    if(!GetModuleFileNameA(0, szIniFile, 1024))
        return "Error getting module path!";
    int len=strlen(szIniFile);
    while(szIniFile[len]!='.' && szIniFile[len]!='\\')
        len--;
    if(szIniFile[len]=='\\')
        strcat(szIniFile, ".ini");
    else
        strcpy(&szIniFile[len], ".ini");
    ///GUI Load
    hInstGui=LoadLibraryA(gui_lib); //Sigma
    if(!hInstGui)
        return "Error loading GUI library ("gui_lib")!";
    //_gui_guiinit
    _gui_guiinit=(GUIGUIINIT)GetProcAddress(hInstGui, "_gui_guiinit");
    if(!_gui_guiinit)
        return "Export \"_gui_guiinit\" could not be found!";
    //_gui_sendmessage;
    _gui_sendmessage=(GUISENDMESSAGE)GetProcAddress(hInstGui, "_gui_sendmessage");
    if(!_gui_sendmessage)
        return "Export \"_gui_sendmessage\" could not be found!";

    ///DBG Load
    hInstDbg=LoadLibraryA(dbg_lib); //Mr. eXoDia
    if(!hInstDbg)
        return "Error loading debugger library ("dbg_lib")!";
    //_dbg_dbginit
    _dbg_dbginit=(DBGDBGINIT)GetProcAddress(hInstDbg, "_dbg_dbginit");
    if(!_dbg_dbginit)
        return "Export \"_dbg_dbginit\" could not be found!";
    //_dbg_memfindbaseaddr
    _dbg_memfindbaseaddr=(DBGMEMFINDBASEADDR)GetProcAddress(hInstDbg, "_dbg_memfindbaseaddr");
    if(!_dbg_memfindbaseaddr)
        return "Export \"_dbg_memfindbaseaddr\" could not be found!";
    //_dbg_memread
    _dbg_memread=(DBGMEMREAD)GetProcAddress(hInstDbg, "_dbg_memread");
    if(!_dbg_memread)
        return "Export \"_dbg_memread\" could not be found!";
    //_dbg_memwrite
    _dbg_memwrite=(DBGMEMWRITE)GetProcAddress(hInstDbg, "_dbg_memwrite");
    if(!_dbg_memwrite)
        return "Export \"_dbg_memwrite\" could not be found!";
    //_dbg_dbgcmdexec
    _dbg_dbgcmdexec=(DBGDBGCMDEXEC)GetProcAddress(hInstDbg, "_dbg_dbgcmdexec");
    if(!_dbg_dbgcmdexec)
        return "Export \"_dbg_dbgcmdexec\" could not be found!";
    //_dbg_memmap
    _dbg_memmap=(DBGMEMMAP)GetProcAddress(hInstDbg, "_dbg_memmap");
    if(!_dbg_memmap)
        return "Export \"_dbg_memmap\" could not be found!";
    //_dbg_dbgexitsignal
    _dbg_dbgexitsignal=(DBGDBGEXITSIGNAL)GetProcAddress(hInstDbg, "_dbg_dbgexitsignal");
    if(!_dbg_dbgexitsignal)
        return "Export \"_dbg_dbgexitsignal\" could not be found!";
    //_dbg_valfromstring
    _dbg_valfromstring=(DBGVALFROMSTRING)GetProcAddress(hInstDbg, "_dbg_valfromstring");
    if(!_dbg_valfromstring)
        return "Export \"_dbg_valfromstring\" could not be found!";
    //_dbg_isdebugging
    _dbg_isdebugging=(DBGISDEBUGGING)GetProcAddress(hInstDbg, "_dbg_isdebugging");
    if(!_dbg_isdebugging)
        return "Export \"_dbg_isdebugging\" could not be found!";
    //_dbg_isjumpgoingtoexecute
    _dbg_isjumpgoingtoexecute=(DBGISJUMPGOINGTOEXECUTE)GetProcAddress(hInstDbg, "_dbg_isjumpgoingtoexecute");
    if(!_dbg_isjumpgoingtoexecute)
        return "Export \"_dbg_isjumpgoingtoexecute\" could not be found!";
    //_dbg_addrinfoget
    _dbg_addrinfoget=(DBGADDRINFOGET)GetProcAddress(hInstDbg, "_dbg_addrinfoget");
    if(!_dbg_addrinfoget)
        return "Export \"_dbg_addrinfoget\" could not be found!";
    //_dbg_addrinfoset
    _dbg_addrinfoset=(DBGADDRINFOSET)GetProcAddress(hInstDbg, "_dbg_addrinfoset");
    if(!_dbg_addrinfoset)
        return "Export \"_dbg_addrinfoset\" could not be found!";
    //_dbg_bpgettypeat
    _dbg_bpgettypeat=(DBGBPGETTYPEAT)GetProcAddress(hInstDbg, "_dbg_bpgettypeat");
    if(!_dbg_bpgettypeat)
        return "Export \"_dbg_bpgettypeat\" could not be found!";
    //_dbg_getregdump
    _dbg_getregdump=(DBGGETREGDUMP)GetProcAddress(hInstDbg, "_dbg_getregdump");
    if(!_dbg_getregdump)
        return "Export \"_dbg_getregdump\" could not be found!";
    //_dbg_valtostring
    _dbg_valtostring=(DBGVALTOSTRING)GetProcAddress(hInstDbg, "_dbg_valtostring");
    if(!_dbg_valtostring)
        return "Export \"_dbg_valtostring\" could not be found!";
    //_dbg_memisvalidreadptr
    _dbg_memisvalidreadptr=(DBGMEMISVALIDREADPTR)GetProcAddress(hInstDbg, "_dbg_memisvalidreadptr");
    if(!_dbg_memisvalidreadptr)
        return "Export \"_dbg_memisvalidreadptr\" could not be found!";
    //_dbg_getbplist
    _dbg_getbplist=(DBGGETBPLIST)GetProcAddress(hInstDbg, "_dbg_getbplist");
    if(!_dbg_getbplist)
        return "Export \"_dbg_getbplist\" could not be found!";
    //_dbg_dbgcmddirectexec
    _dbg_dbgcmddirectexec=(DBGDBGCMDEXECDIRECT)GetProcAddress(hInstDbg, "_dbg_dbgcmddirectexec");
    if(!_dbg_dbgcmddirectexec)
        return "Export \"_dbg_dbgcmddirectexec\" could not be found!";
    //_dbg_getbranchdestination
    _dbg_getbranchdestination=(DBGGETBRANCHDESTINATION)GetProcAddress(hInstDbg, "_dbg_getbranchdestination");
    if(!_dbg_getbranchdestination)
        return "Export \"_dbg_getbranchdestination\" could not be found!";
    //_dbg_functionoverlaps
    _dbg_functionoverlaps=(DBGFUNCTIONOVERLAPS)GetProcAddress(hInstDbg, "_dbg_functionoverlaps");
    if(!_dbg_functionoverlaps)
        return "Export \"_dbg_functionoverlaps\" could not be found!";
    //_dbg_sendmessage
    _dbg_sendmessage=(DBGSENDMESSAGE)GetProcAddress(hInstDbg, "_dbg_sendmessage");
    if(!_dbg_sendmessage)
        return "Export \"_dbg_sendmessage\" could not be found!";
    return 0;
}

BRIDGE_IMPEXP const char* BridgeStart()
{
    if(!_dbg_dbginit || !_gui_guiinit)
        return "\"_dbg_dbginit\" || \"_gui_guiinit\" was not loaded yet, call BridgeInit!";
    _gui_guiinit(0, 0); //remove arguments
    _dbg_dbgexitsignal(); //send exit signal to debugger
    return 0;
}

BRIDGE_IMPEXP void* BridgeAlloc(size_t size)
{
    //unsigned char* a=(unsigned char*)VirtualAlloc(0, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    unsigned char* a=new (std::nothrow)unsigned char[size];
    if(!a)
    {
        MessageBoxA(0, "Could not allocate memory", "Error", MB_ICONERROR);
        ExitProcess(1);
    }
    memset(a, 0, size);
    return a;
}

BRIDGE_IMPEXP void BridgeFree(void* ptr)
{
    //VirtualFree(ptr, 0, MEM_RELEASE);
    delete[] (unsigned char*)ptr;
}

BRIDGE_IMPEXP bool BridgeSettingGet(const char* section, const char* key, char* value)
{
    if(!section || !key || !value)
        return false;
    if(!GetPrivateProfileStringA(section, key, "", value, MAX_SETTING_SIZE, szIniFile))
        return false;
    return true;
}

BRIDGE_IMPEXP bool BridgeSettingGetUint(const char* section, const char* key, duint* value)
{
    if(!section || !key || !value)
        return false;
    char newvalue[MAX_SETTING_SIZE]="";
    if(!BridgeSettingGet(section, key, newvalue))
        return false;
#ifdef _WIN64
    int ret=sscanf(newvalue, "%llX", value);
#else
    int ret=sscanf(newvalue, "%X", value);
#endif //_WIN64
    if(ret)
        return true;
    return false;
}

BRIDGE_IMPEXP bool BridgeSettingSet(const char* section, const char* key, const char* value)
{
    if(!section || !key || !value)
        return false;
    if(!WritePrivateProfileStringA(section, key, value, szIniFile))
        return false;
    return true;
}

BRIDGE_IMPEXP bool BridgeSettingSetUint(const char* section, const char* key, duint value)
{
    if(!section || !key)
        return false;
    char newvalue[MAX_SETTING_SIZE]="";
#ifdef _WIN64
    sprintf(newvalue, "%llX", value);
#else
    sprintf(newvalue, "%X", value);
#endif //_WIN64
    return BridgeSettingSet(section, key, newvalue);
}

//Debugger
BRIDGE_IMPEXP bool DbgMemRead(duint va, unsigned char* dest, duint size)
{
    bool ret=_dbg_memread(va, dest, size, 0);
    if(!ret)
        memset(dest, 0x90, size);
    return ret;
}

BRIDGE_IMPEXP bool DbgMemWrite(duint va, const unsigned char* src, duint size)
{
    return _dbg_memwrite(va, src, size, 0);
}

BRIDGE_IMPEXP duint DbgMemGetPageSize(duint base)
{
    duint size=0;
    _dbg_memfindbaseaddr(base, &size);
    return size;
}

BRIDGE_IMPEXP duint DbgMemFindBaseAddr(duint addr, duint* size)
{
    return _dbg_memfindbaseaddr(addr, size);
}

BRIDGE_IMPEXP bool DbgCmdExec(const char* cmd)
{
    return _dbg_dbgcmdexec(cmd);
}

BRIDGE_IMPEXP bool DbgMemMap(MEMMAP* memmap)
{
    return _dbg_memmap(memmap);
}

BRIDGE_IMPEXP bool DbgIsValidExpression(const char* expression)
{
    duint value=0;
    return _dbg_valfromstring(expression, &value);
}

BRIDGE_IMPEXP bool DbgIsDebugging()
{
    return _dbg_isdebugging();
}

BRIDGE_IMPEXP bool DbgIsJumpGoingToExecute(duint addr)
{
    return _dbg_isjumpgoingtoexecute(addr);
}

BRIDGE_IMPEXP bool DbgGetLabelAt(duint addr, SEGMENTREG segment, char* text) //(module.)+label
{
    if(!text || !addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flaglabel;
    if(!_dbg_addrinfoget(addr, segment, &info))
    {
        duint addr_=0;
        if(!DbgMemIsValidReadPtr(addr))
            return false;
        DbgMemRead(addr, (unsigned char*)&addr_, sizeof(duint));
        if(!_dbg_addrinfoget(addr_, SEG_DEFAULT, &info))
            return false;
    }
    strcpy(text, info.label);
    return true;
}

BRIDGE_IMPEXP bool DbgSetLabelAt(duint addr, const char* text)
{
    if(!text || strlen(text)>=MAX_LABEL_SIZE || !addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flaglabel;
    strcpy(info.label, text);
    if(!_dbg_addrinfoset(addr, &info))
        return false;
    return true;
}

BRIDGE_IMPEXP bool DbgGetCommentAt(duint addr, char* text) //comment (not live)
{
    if(!text || !addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagcomment;
    if(!_dbg_addrinfoget(addr, SEG_DEFAULT, &info))
        return false;
    strcpy(text, info.comment);
    return true;
}

BRIDGE_IMPEXP bool DbgSetCommentAt(duint addr, const char* text)
{
    if(!text || strlen(text)>=MAX_COMMENT_SIZE || !addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagcomment;
    strcpy(info.comment, text);
    if(!_dbg_addrinfoset(addr, &info))
        return false;
    return true;
}

BRIDGE_IMPEXP bool DbgGetModuleAt(duint addr, char* text)
{
    if(!text || !addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagmodule;
    if(!_dbg_addrinfoget(addr, SEG_DEFAULT, &info))
        return false;
    strcpy(text, info.module);
    return true;
}

BRIDGE_IMPEXP bool DbgGetBookmarkAt(duint addr)
{
    if(!addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagbookmark;
    if(!_dbg_addrinfoget(addr, SEG_DEFAULT, &info))
        return false;
    return info.isbookmark;
}

BRIDGE_IMPEXP bool DbgSetBookmarkAt(duint addr, bool isbookmark)
{
    if(!addr)
        return false;
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagbookmark;
    info.isbookmark=isbookmark;
    return _dbg_addrinfoset(addr, &info);
}

BRIDGE_IMPEXP const char* DbgInit()
{
    return _dbg_dbginit();
}

BRIDGE_IMPEXP BPXTYPE DbgGetBpxTypeAt(duint addr)
{
    return _dbg_bpgettypeat(addr);
}

BRIDGE_IMPEXP duint DbgValFromString(const char* string)
{
    duint value=0;
    _dbg_valfromstring(string, &value);
    return value;
}

BRIDGE_IMPEXP bool DbgGetRegDump(REGDUMP* regdump)
{
    return _dbg_getregdump(regdump);
}

BRIDGE_IMPEXP bool DbgValToString(const char* string, duint value)
{
    duint valueCopy=value;
    return _dbg_valtostring(string, &valueCopy);
}

BRIDGE_IMPEXP bool DbgMemIsValidReadPtr(duint addr)
{
    return _dbg_memisvalidreadptr(addr);
}

BRIDGE_IMPEXP int DbgGetBpList(BPXTYPE type, BPMAP* list)
{
    return _dbg_getbplist(type, list);
}

BRIDGE_IMPEXP bool DbgCmdExecDirect(const char* cmd)
{
    return _dbg_dbgcmddirectexec(cmd);
}

BRIDGE_IMPEXP FUNCTYPE DbgGetFunctionTypeAt(duint addr)
{
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagfunction;
    if(!_dbg_addrinfoget(addr, SEG_DEFAULT, &info))
        return FUNC_NONE;
    duint start=info.function.start;
    duint end=info.function.end;
    if(start==end)
        return FUNC_SINGLE;
    else if(addr==start)
        return FUNC_BEGIN;
    else if(addr==end)
        return FUNC_END;
    return FUNC_MIDDLE;
}

BRIDGE_IMPEXP LOOPTYPE DbgGetLoopTypeAt(duint addr, int depth)
{
    //NOTE: test code for 'function.exe'
    /*if(depth==0)
    {
        if(addr==0x00401348)
            return LOOP_BEGIN;
        else if(addr==0x004013A8)
            return LOOP_ENTRY;
        else if(addr>0x00401348 && addr<0x004013B3)
            return LOOP_MIDDLE;
        else if(addr==0x004013B3)
            return LOOP_END;
    }
    else if(depth==1)
    {
        if(addr==0x00401351)
            return LOOP_BEGIN;
        else if(addr==0x00401398)
            return LOOP_ENTRY;
        else if(addr>0x00401351 && addr<0x004013A3)
            return LOOP_MIDDLE;
        else if(addr==0x004013A3)
            return LOOP_END;
    }
    else if(depth==2)
    {
        if(addr==0x0040135A)
            return LOOP_BEGIN;
        else if(addr==0x00401388)
            return LOOP_ENTRY;
        else if(addr>0x0040135A && addr<0x00401393)
            return LOOP_MIDDLE;
        else if(addr==0x00401393)
            return LOOP_END;
    }*/
    return LOOP_NONE;
}

BRIDGE_IMPEXP duint DbgGetBranchDestination(duint addr)
{
    return _dbg_getbranchdestination(addr);
}

BRIDGE_IMPEXP bool DbgFunctionOverlaps(duint start, duint end)
{
    return _dbg_functionoverlaps(start, end);
}

BRIDGE_IMPEXP bool DbgFunctionGet(duint addr, duint* start, duint* end)
{
    ADDRINFO info;
    memset(&info, 0, sizeof(info));
    info.flags=flagfunction;
    if(!_dbg_addrinfoget(addr, SEG_DEFAULT, &info))
        return false;
    if(start)
        *start=info.function.start;
    if(end)
        *end=info.function.end;
    return true;
}

BRIDGE_IMPEXP void DbgScriptLoad(const char* filename)
{
    _dbg_sendmessage(DBG_SCRIPT_LOAD, (void*)filename, 0);
}

BRIDGE_IMPEXP void DbgScriptUnload()
{
    _dbg_sendmessage(DBG_SCRIPT_UNLOAD, 0, 0);
}

BRIDGE_IMPEXP void DbgScriptRun(int destline)
{
    _dbg_sendmessage(DBG_SCRIPT_RUN, (void*)(duint)destline, 0);
}

BRIDGE_IMPEXP void DbgScriptStep()
{
    _dbg_sendmessage(DBG_SCRIPT_STEP, 0, 0);
}

BRIDGE_IMPEXP bool DbgScriptBpToggle(int line)
{
    if(_dbg_sendmessage(DBG_SCRIPT_BPTOGGLE, (void*)(duint)line, 0))
        return true;
    return false;
}

BRIDGE_IMPEXP bool DbgScriptBpGet(int line)
{
    if(_dbg_sendmessage(DBG_SCRIPT_BPGET, (void*)(duint)line, 0))
        return true;
    return false;
}

BRIDGE_IMPEXP bool DbgScriptCmdExec(const char* command)
{
    if(_dbg_sendmessage(DBG_SCRIPT_CMDEXEC, (void*)command, 0))
        return true;
    return false;
}

BRIDGE_IMPEXP void DbgScriptAbort()
{
    _dbg_sendmessage(DBG_SCRIPT_ABORT, 0, 0);
}

BRIDGE_IMPEXP SCRIPTLINETYPE DbgScriptGetLineType(int line)
{
    return (SCRIPTLINETYPE)_dbg_sendmessage(DBG_SCRIPT_GETLINETYPE, (void*)(duint)line, 0);
}

BRIDGE_IMPEXP void DbgScriptSetIp(int line)
{
    _dbg_sendmessage(DBG_SCRIPT_SETIP, (void*)(duint)line, 0);
}

BRIDGE_IMPEXP void DbgSymbolEnum(duint base, CBSYMBOLENUM cbSymbolEnum, void* user)
{
    SYMBOLCBINFO cbInfo;
    cbInfo.base=base;
    cbInfo.cbSymbolEnum=cbSymbolEnum;
    cbInfo.user=user;
    _dbg_sendmessage(DBG_SYMBOL_ENUM, &cbInfo, 0);
}

BRIDGE_IMPEXP bool DbgAssembleAt(duint addr, const char* instruction)
{
    if(_dbg_sendmessage(DBG_ASSEMBLE_AT, (void*)addr, (void*)instruction))
        return true;
    return false;
}

BRIDGE_IMPEXP duint DbgModBaseFromName(const char* name)
{
    return _dbg_sendmessage(DBG_MODBASE_FROM_NAME, (void*)name, 0);
}

BRIDGE_IMPEXP void DbgDisasmAt(duint addr, DISASM_INSTR* instr)
{
    _dbg_sendmessage(DBG_DISASM_AT, (void*)addr, instr);
}

BRIDGE_IMPEXP bool DbgStackCommentGet(duint addr, STACK_COMMENT* comment)
{
    return (bool)(duint)_dbg_sendmessage(DBG_STACK_COMMENT_GET, (void*)addr, comment);
}

BRIDGE_IMPEXP void DbgGetThreadList(THREADLIST* list)
{
    _dbg_sendmessage(DBG_GET_THREAD_LIST, list, 0);
}

BRIDGE_IMPEXP void DbgSettingsUpdated()
{
    _dbg_sendmessage(DBG_SETTINGS_UPDATED, 0, 0);
}

BRIDGE_IMPEXP void DbgDisasmFastAt(duint addr, BASIC_INSTRUCTION_INFO* basicinfo)
{
    _dbg_sendmessage(DBG_DISASM_FAST_AT, (void*)addr, basicinfo);
}

//GUI
BRIDGE_IMPEXP void GuiDisasmAt(duint addr, duint cip)
{
    _gui_sendmessage(GUI_DISASSEMBLE_AT, (void*)addr, (void*)cip);
}

BRIDGE_IMPEXP void GuiSetDebugState(DBGSTATE state)
{
    _gui_sendmessage(GUI_SET_DEBUG_STATE, (void*)state, 0);
}

BRIDGE_IMPEXP void GuiAddLogMessage(const char* msg)
{
    _gui_sendmessage(GUI_ADD_MSG_TO_LOG, (void*)msg, 0);
}

BRIDGE_IMPEXP void GuiLogClear()
{
    _gui_sendmessage(GUI_CLEAR_LOG, 0, 0);
}

BRIDGE_IMPEXP void GuiUpdateAllViews()
{
    GuiUpdateRegisterView();
    GuiUpdateDisassemblyView();
    GuiUpdateBreakpointsView();
    GuiUpdateDumpView();
    GuiUpdateThreadView();
}

BRIDGE_IMPEXP void GuiUpdateRegisterView()
{
    _gui_sendmessage(GUI_UPDATE_REGISTER_VIEW, 0, 0);
}

BRIDGE_IMPEXP void GuiUpdateDisassemblyView()
{
    _gui_sendmessage(GUI_UPDATE_DISASSEMBLY_VIEW, 0, 0);
}

BRIDGE_IMPEXP void GuiUpdateBreakpointsView()
{
    _gui_sendmessage(GUI_UPDATE_BREAKPOINTS_VIEW, 0, 0);
}

BRIDGE_IMPEXP void GuiUpdateWindowTitle(const char* filename)
{
    _gui_sendmessage(GUI_UPDATE_WINDOW_TITLE, (void*)filename, 0);
}

BRIDGE_IMPEXP HWND GuiGetWindowHandle()
{
    return (HWND)_gui_sendmessage(GUI_GET_WINDOW_HANDLE, 0, 0);
}

BRIDGE_IMPEXP void GuiDumpAt(duint va)
{
    _gui_sendmessage(GUI_DUMP_AT, (void*)va, 0);
}

BRIDGE_IMPEXP void GuiScriptAdd(int count, const char** lines)
{
    _gui_sendmessage(GUI_SCRIPT_ADD, (void*)(duint)count, (void*)lines);
}

BRIDGE_IMPEXP void GuiScriptClear()
{
    _gui_sendmessage(GUI_SCRIPT_CLEAR, 0, 0);
}

BRIDGE_IMPEXP void GuiScriptSetIp(int line)
{
    _gui_sendmessage(GUI_SCRIPT_SETIP, (void*)(duint)line, 0);
}

BRIDGE_IMPEXP void GuiScriptError(int line, const char* message)
{
    _gui_sendmessage(GUI_SCRIPT_ERROR, (void*)(duint)line, (void*)message);
}

BRIDGE_IMPEXP void GuiScriptSetTitle(const char* title)
{
    _gui_sendmessage(GUI_SCRIPT_SETTITLE, (void*)title, 0);
}

BRIDGE_IMPEXP void GuiScriptSetInfoLine(int line, const char* info)
{
    _gui_sendmessage(GUI_SCRIPT_SETINFOLINE, (void*)(duint)line, (void*)info);
}

BRIDGE_IMPEXP void GuiScriptMessage(const char* message)
{
    _gui_sendmessage(GUI_SCRIPT_MESSAGE, (void*)message, 0);
}

BRIDGE_IMPEXP int GuiScriptMsgyn(const char* message)
{
    return (int)(duint)_gui_sendmessage(GUI_SCRIPT_MSGYN, (void*)message, 0);
}

BRIDGE_IMPEXP void GuiSymbolLogAdd(const char* message)
{
    _gui_sendmessage(GUI_SYMBOL_LOG_ADD, (void*)message, 0);
}

BRIDGE_IMPEXP void GuiSymbolLogClear()
{
    _gui_sendmessage(GUI_SYMBOL_LOG_CLEAR, 0, 0);
}

BRIDGE_IMPEXP void GuiSymbolSetProgress(int percent)
{
    _gui_sendmessage(GUI_SYMBOL_SET_PROGRESS, (void*)(duint)percent, 0);
}

BRIDGE_IMPEXP void GuiSymbolUpdateModuleList(int count, SYMBOLMODULEINFO* modules)
{
    _gui_sendmessage(GUI_SYMBOL_UPDATE_MODULE_LIST, (void*)(duint)count, (void*)modules);
}

BRIDGE_IMPEXP void GuiReferenceAddColumn(int width, const char* title)
{
    _gui_sendmessage(GUI_REF_ADDCOLUMN, (void*)(duint)width, (void*)title);
}

BRIDGE_IMPEXP void GuiReferenceSetRowCount(int count)
{
    _gui_sendmessage(GUI_REF_SETROWCOUNT, (void*)(duint)count, 0);
}

BRIDGE_IMPEXP int GuiReferenceGetRowCount()
{
    return (int)(duint)_gui_sendmessage(GUI_REF_GETROWCOUNT, 0, 0);
}

BRIDGE_IMPEXP void GuiReferenceDeleteAllColumns()
{
    _gui_sendmessage(GUI_REF_DELETEALLCOLUMNS, 0, 0);
}

BRIDGE_IMPEXP void GuiReferenceSetCellContent(int row, int col, const char* str)
{
    CELLINFO info;
    info.row=row;
    info.col=col;
    info.str=str;
    _gui_sendmessage(GUI_REF_SETCELLCONTENT, &info, 0);
}

BRIDGE_IMPEXP const char* GuiReferenceGetCellContent(int row, int col)
{
    return (const char*)_gui_sendmessage(GUI_REF_GETCELLCONTENT, (void*)(duint)row, (void*)(duint)col);
}

BRIDGE_IMPEXP void GuiReferenceReloadData()
{
    _gui_sendmessage(GUI_REF_RELOADDATA, 0, 0);
}

BRIDGE_IMPEXP void GuiReferenceSetSingleSelection(int index, bool scroll)
{
    _gui_sendmessage(GUI_REF_SETSINGLESELECTION, (void*)(duint)index, (void*)(duint)scroll);
}

BRIDGE_IMPEXP void GuiReferenceSetProgress(int progress)
{
    _gui_sendmessage(GUI_REF_SETPROGRESS, (void*)(duint)progress, 0);
}

BRIDGE_IMPEXP void GuiReferenceSetSearchStartCol(int col)
{
    _gui_sendmessage(GUI_REF_SETSEARCHSTARTCOL, (void*)(duint)col, 0);
}

BRIDGE_IMPEXP void GuiStackDumpAt(duint addr, duint csp)
{
    _gui_sendmessage(GUI_STACK_DUMP_AT, (void*)addr, (void*)csp);
}

BRIDGE_IMPEXP void GuiUpdateDumpView()
{
    _gui_sendmessage(GUI_UPDATE_DUMP_VIEW, 0, 0);
}

BRIDGE_IMPEXP void GuiUpdateThreadView()
{
    _gui_sendmessage(GUI_UPDATE_THREAD_VIEW, 0, 0);
}

BRIDGE_IMPEXP void GuiAddRecentFile(const char* file)
{
    _gui_sendmessage(GUI_ADD_RECENT_FILE, (void*)file, 0);
}

BRIDGE_IMPEXP void GuiSetLastException(unsigned int exception)
{
    _gui_sendmessage(GUI_SET_LAST_EXCEPTION, (void*)(duint)exception, 0);
}

BRIDGE_IMPEXP bool GuiGetDisassembly(duint addr, char* text)
{
    return (bool)(duint)_gui_sendmessage(GUI_GET_DISASSEMBLY, (void*)addr, text);
}

BRIDGE_IMPEXP int GuiMenuAdd(int hMenu, const char* title)
{
    return (int)(duint)_gui_sendmessage(GUI_MENU_ADD, (void*)(duint)hMenu, (void*)title);
}

BRIDGE_IMPEXP int GuiMenuAddEntry(int hMenu, const char* title)
{
    return (int)(duint)_gui_sendmessage(GUI_MENU_ADD_ENTRY, (void*)(duint)hMenu, (void*)title);
}

BRIDGE_IMPEXP void GuiMenuAddSeparator(int hMenu)
{
    _gui_sendmessage(GUI_MENU_ADD_SEPARATOR, (void*)(duint)hMenu, 0);
}

BRIDGE_IMPEXP void GuiMenuClear(int hMenu)
{
    _gui_sendmessage(GUI_MENU_CLEAR, (void*)(duint)hMenu, 0);
}

//Main
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    hInst=hinstDLL;
    return TRUE;
}

