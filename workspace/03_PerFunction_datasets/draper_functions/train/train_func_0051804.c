DoInitializations(const wxString& filename, LoaderBase* fileLdr)

{


    m_pData = new ScbEditorInternalData(this);

    m_pData->m_pFileLoader = fileLdr;
    m_IsBuiltinEditor = true;

    if (!filename.IsEmpty())
    {
        InitFilename(filename);
        wxFileName fname(m_Filename);
        NormalizePath(fname, wxEmptyString);
        m_Filename = fname.GetFullPath();
    }
    else
    {
        static int untitledCounter = 1;
        wxString f;
        cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
        if (prj)
            f.Printf(_("%sUntitled%d"), prj->GetBasePath().c_str(), untitledCounter++);
        else
            f.Printf(_("Untitled%d"), untitledCounter++);

        InitFilename(f);
    }


    Freeze();
    m_pSizer = new wxBoxSizer(wxVERTICAL);
    m_pControl = CreateEditor();
    m_pSizer->Add(m_pControl, 1, wxEXPAND);
    SetSizer(m_pSizer);


    Thaw();
    m_pControl->SetZoom(GetEditorManager()->GetZoom());
    m_pSizer->SetItemMinSize(m_pControl, 32, 32);

    SetEditorStyleBeforeFileOpen();
    m_IsOK = Open();
    SetEditorStyleAfterFileOpen();


    if (!m_IsOK || filename.IsEmpty())
    {
        SetModified(true);
        m_IsOK = false;
    }
}
