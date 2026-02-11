SaveTools()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("tools"));
    wxArrayString list = cfg->EnumerateSubPaths(_("/"));
    for (unsigned int i = 0; i < list.GetCount(); ++i)
    {
        cfg->DeleteSubPath(list[i]);
    }

    int count = 0;
    for (ToolsList::Node* node = m_Tools.GetFirst(); node; node = node->GetNext())
    {
        cbTool* tool = node->GetData();
        wxString elem;


        wxString tmp;
        tmp.Printf(_T("tool%2.2d"), count++);

        elem << _T("/") << tmp  << _T("/");
        cfg->Write(elem + _T("name"), tool->GetName());
        cfg->Write(elem + _T("command"), tool->GetCommand());
        cfg->Write(elem + _T("params"), tool->GetParams());
        cfg->Write(elem + _T("workingDir"), tool->GetWorkingDir());
        cfg->Write(elem + _T("launchOption"), static_cast<int>(tool->GetLaunchOption()));
    }
}
