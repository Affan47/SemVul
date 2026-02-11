DeleteGUI(void)
{
    _gui = NULL;
    delete _guithread;
    _guithread = NULL;
    if(GetScripts()->ScriptExists("_onguiclose"))
        AddCliCommand("_onguiclose");


#if PLATFORM == PLATFORM_WIN32 && !defined(_CONSOLE)
    this->Stop();
#endif
}
