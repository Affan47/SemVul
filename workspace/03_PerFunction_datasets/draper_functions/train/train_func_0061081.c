ScriptConsolePrintFunc(HSQUIRRELVM , const SQChar * s, ...)
{
    static SQChar temp[2048];
    va_list vl;
    va_start(vl,s);
    scvsprintf( temp,s,vl);
    wxString msg = cbC2U(temp);
    va_end(vl);

    if (s_Console)
        s_Console->Log(msg);
    Manager::Get()->GetScriptingManager()->InjectScriptOutput(msg);
}
