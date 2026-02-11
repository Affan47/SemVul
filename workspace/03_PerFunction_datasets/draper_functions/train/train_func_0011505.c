OnCmdLineParsed(wxCmdLineParser &parser) {

    wxApp::OnCmdLineParsed(parser);
    wxString portNum = wxEmptyString;
    long longPort;
    bool hostNameSpecified = false;
    bool passwordSpecified = false;

    parser.Found(wxT("boincargs"), &m_strBOINCArguments);
    if (parser.Found(wxT("autostart"))) {
        m_bBOINCMGRAutoStarted = true;
    }
#if defined(__WXMSW__) || defined(__WXMAC__)
    if (parser.Found(wxT("systray"))) {
        m_bGUIVisible = false;
    }
#endif
    if (parser.Found(wxT("insecure"))) {
        g_use_sandbox = false;
    }
    if (parser.Found(wxT("checkskins"))) {
        m_bDebugSkins = true;
    }
    if (parser.Found(wxT("multiple"))) {
        m_bMultipleInstancesOK = true;
    }

#if !(defined(__WXMSW__) || defined(__WXMAC__))
    if (!parser.Found(wxT("clientdir"), &m_strBOINCMGRRootDirectory)) {
        m_strBOINCMGRRootDirectory = ::wxGetCwd();
    }
    if (m_strBOINCMGRRootDirectory.Last() != '/') {
        m_strBOINCMGRRootDirectory.Append('/');
    }

    if (!parser.Found(wxT("datadir"), &m_strBOINCMGRDataDirectory)) {
        m_strBOINCMGRDataDirectory = m_strBOINCMGRRootDirectory;
    }
    if (m_strBOINCMGRDataDirectory.Last() != '/') {
        m_strBOINCMGRDataDirectory.Append('/');
    }
#endif

    if (parser.Found(wxT("namehost"), &m_strHostNameArg)) {
        hostNameSpecified = true;
    } else {
        m_strHostNameArg = wxT("localhost");
    }

     if (parser.Found(wxT("gui_rpc_port"), &portNum)) {
        if (portNum.ToLong(&longPort)) {
            m_iRPCPortArg = longPort;
        } else {
            m_iRPCPortArg = GUI_RPC_PORT;
        }
    } else {
        m_iRPCPortArg = GUI_RPC_PORT;
    }

    if (parser.Found(wxT("password"), &m_strPasswordArg)) {
        passwordSpecified = true;
    } else {
        m_strPasswordArg = wxEmptyString;
    }

    if (hostNameSpecified && passwordSpecified) {
        m_bMultipleInstancesOK = true;
    }
    return true;
}
