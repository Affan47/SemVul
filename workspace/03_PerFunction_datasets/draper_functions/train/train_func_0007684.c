GetFlag(Flags flag)
{
    switch (flag)
    {
        case WatchFuncArgs:
            return m_config.ReadBool(wxT("watch_args"), true);
        case WatchLocals:
            return m_config.ReadBool(wxT("watch_locals"), true);
        case WatchScriptPrinters:
            return m_config.ReadBool(wxT("watch_script_printers"), true);
        case CatchExceptions:
            return m_config.ReadBool(wxT("catch_exceptions"), true);
        case EvalExpression:
            return m_config.ReadBool(wxT("eval_tooltip"), false);
        case AddOtherProjectDirs:
            return m_config.ReadBool(wxT("add_other_search_dirs"), false);
        case DoNotRun:
            return m_config.ReadBool(wxT("do_not_run"), false);
        default:
            return false;
    }
}
