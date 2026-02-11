BuildTree()
{
    m_pTree = new cbTreeCtrl(m_pNotebook, ID_ProjectManager);

    static const wxString imgs[] =
    {


        _T("file.png"),
        _T("file-missing.png"),
        _T("file-modified.png"),
        _T("file-readonly.png"),


        _T("rc-file-added.png"),
        _T("rc-file-conflict.png"),
        _T("rc-file-missing.png"),
        _T("rc-file-modified.png"),
        _T("rc-file-outofdate.png"),
        _T("rc-file-uptodate.png"),
        _T("rc-file-requireslock.png"),
        _T("rc-file-external.png"),
        _T("rc-file-gotlock.png"),
        _T("rc-file-lockstolen.png"),
        _T("rc-file-mismatch.png"),
        _T("rc-file-noncontrolled.png"),


        _T("workspace.png"),
        _T("workspace-readonly.png"),
        _T("project.png"),
        _T("project-readonly.png"),
        _T("folder_open.png"),
        _T("vfolder_open.png"),

        wxEmptyString
    };
    wxBitmap bmp;
    m_pImages = new wxImageList(16, 16);
    wxString prefix = ConfigManager::ReadDataPath() + _T("/images/");

    int i = 0;
    while (!imgs[i].IsEmpty())
    {
        bmp = cbLoadBitmap(prefix + imgs[i], wxBITMAP_TYPE_PNG);
        m_pImages->Add(bmp);
        ++i;
    }
    m_pTree->SetImageList(m_pImages);
}
