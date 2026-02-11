RunSingleFile(const wxString& filename)
{
    wxFileName fname(filename);

    if (fname.GetExt() == _T("script"))
    {
        Manager::Get()->GetScriptingManager()->LoadScript(filename);
        return 0;
    }

    m_CdRun = fname.GetPath();
    fname.SetExt(FileFilters::EXECUTABLE_EXT);
    wxString exe_filename = fname.GetFullPath();
    wxString cmd;

    if (!platform::windows)
    {

        wxString term = Manager::Get()->GetConfigManager(_T("app"))->Read(_T("/console_terminal"), DEFAULT_CONSOLE_TERM);
        term.Replace(_T("$TITLE"), _T("'") + exe_filename + _T("'"));
        cmd << term << strSPACE;
    }
    wxString baseDir = ConfigManager::GetExecutableFolder();

    if (wxFileExists(baseDir + strSLASH + strCONSOLE_RUNNER))
        cmd << baseDir << strSLASH << strCONSOLE_RUNNER << strSPACE;

    if (!cmd.Replace(_T("$SCRIPT"), exe_filename))

        cmd << _T("\"") << exe_filename << _T("\"");

    Manager::Get()->GetLogManager()->Log(_("Checking for existence: ") + exe_filename, m_PageIndex);
    if (!wxFileExists(exe_filename))
    {
        int ret = cbMessageBox(_("It seems that this file has not been built yet.\n"
                                "Do you want to build it now?"),
                                _("Information"),
                                wxYES_NO | wxCANCEL | wxICON_QUESTION);
        switch (ret)
        {
            case wxID_YES:
            {
                m_RunAfterCompile = true;
                Build(wxEmptyString);
                return -1;
            }
            case wxID_NO:
                break;
            default:
                return -1;
        }
    }

    Manager::Get()->GetMacrosManager()->ReplaceEnvVars(m_CdRun);
    Manager::Get()->GetLogManager()->Log(F(_("Executing: %s (in %s)"), cmd.wx_str(), m_CdRun.wx_str()), m_PageIndex);
    m_CommandQueue.Add(new CompilerCommand(cmd, wxEmptyString, 0, 0, true));
    return 0;
}
