Save()
{
    ConfigManager* conf = Manager::Get()->GetConfigManager(_T("project_manager"));
    conf->DeleteSubPath(_T("/file_groups"));
    for (unsigned int i = 0; i < m_Groups.GetCount(); ++i)
    {
        FileGroups* fg = m_Groups[i];
        wxString key;
        key << _T("/file_groups/group") << wxString::Format(_T("%u"), i) << _T("/") << _T("name");
        conf->Write(key, fg->groupName);

        key.Clear();
        key << _T("/file_groups/group") << wxString::Format(_T("%u"), i) << _T("/") << _T("mask");

        conf->Write(key, GetStringFromArray( MakeUniqueArray(fg->fileMasks, false), _T(";") ));
    }
}
