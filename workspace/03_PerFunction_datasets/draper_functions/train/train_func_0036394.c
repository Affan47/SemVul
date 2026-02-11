SaveAs()
{
    wxFileName fname;
    fname.Assign(m_Filename);
    ConfigManager* mgr = Manager::Get()->GetConfigManager(_T("app"));
    int StoredIndex = 0;
    wxString Filters = FileFilters::GetFilterString();
    wxString Path = fname.GetPath();
    wxString Extension = fname.GetExt();
    wxString Filter;
    if (!Extension.IsEmpty())
    {

        Extension.Prepend(_T("."));
        Filter = FileFilters::GetFilterString(Extension);
    }
    else if (mgr)
    {

        Filter = mgr->Read(_T("/file_dialogs/save_file_as/filter"), _T("C/C++ files"));
    }
    if (!Filter.IsEmpty())
    {

        int sep = Filter.find(_T("|"));
        if (sep != wxNOT_FOUND)
            Filter.Truncate(sep);
        if (!Filter.IsEmpty())
            FileFilters::GetFilterIndexFromName(Filters, Filter, StoredIndex);
    }
    if (mgr && Path.IsEmpty())
        Path = mgr->Read(_T("/file_dialogs/save_file_as/directory"), Path);

    wxFileDialog dlg(Manager::Get()->GetAppWindow(),
                                         _("Save file"),
                                         Path,
                                         fname.GetFullName(),
                                         Filters,
                                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    dlg.SetFilterIndex(StoredIndex);
    PlaceWindow(&dlg);
    if (dlg.ShowModal() != wxID_OK)
    {
        return false;
    }
    m_Filename = dlg.GetPath();
    Manager::Get()->GetLogManager()->Log(m_Filename);
    fname.Assign(m_Filename);
    m_Shortname = fname.GetFullName();
    SetEditorTitle(m_Shortname);


    SetProjectFile(nullptr);

    m_IsOK = true;
    SetLanguage( HL_AUTO );
    SetModified(true);
    SetEditorStyleAfterFileOpen();
    OverrideUseTabsPerLanguage(m_pControl);
    OverrideUseTabsPerLanguage(m_pControl2);

    if (mgr)
    {
        int Index = dlg.GetFilterIndex();
        Filter.Empty();
        if (FileFilters::GetFilterNameFromIndex(Filters, Index, Filter))
            mgr->Write(_T("/file_dialogs/save_file_as/filter"), Filter);
        wxString Test = dlg.GetDirectory();
        mgr->Write(_T("/file_dialogs/save_file_as/directory"), dlg.GetDirectory());
    }
    return Save();
}
