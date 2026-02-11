Open(bool detectEncoding)
{
    if (m_pProjectFile)
    {
        if (!wxFileExists(m_Filename))
            m_pProjectFile->SetFileState(fvsMissing);
        else if (!wxFile::Access(m_Filename.c_str(), wxFile::write))
            m_pProjectFile->SetFileState(fvsReadOnly);
    }

    if (!wxFileExists(m_Filename))
        return false;


    m_pControl->SetReadOnly(false);
    wxString st;

    m_pControl->ClearAll();
    m_pControl->SetModEventMask(0);

    if (!m_pData)
        return false;

    if (!m_pData->m_pFileLoader)
    {
        m_pData->m_pFileLoader = Manager::Get()->GetFileManager()->Load(m_Filename, false);
    }

    EncodingDetector enc((wxByte*)m_pData->m_pFileLoader->GetData(), m_pData->m_pFileLoader->GetLength());
    st = enc.GetWxStr();
    if (detectEncoding)
    {
        m_pData->m_useByteOrderMark = enc.UsesBOM();
        m_pData->m_byteOrderMarkLength = enc.GetBOMSizeInBytes();
        m_pData->m_encoding = enc.GetFontEncoding();

        SetEncoding(enc.GetFontEncoding());
        m_pData->m_byteOrderMarkLength = enc.GetBOMSizeInBytes();
        SetUseBom(m_pData->m_byteOrderMarkLength > 0);
    }

    m_pControl->InsertText(0, st);
    m_pControl->EmptyUndoBuffer();
    m_pControl->SetModEventMask(wxSCI_MODEVENTMASKALL);


    bool read_only = !wxFile::Access(m_Filename.c_str(), wxFile::write);
    m_pControl->SetReadOnly(read_only);


    if (Manager::Get()->GetConfigManager(_T("editor"))->ReadBool(_T("/folding/fold_all_on_open"), false))
        FoldAll();

    wxFileName fname(m_Filename);
    m_LastModified = fname.GetModificationTime();

    SetModified(false);
    NotifyPlugins(cbEVT_EDITOR_OPEN);

    m_pControl->SetZoom(GetEditorManager()->GetZoom());
    if (m_pControl2)
        m_pControl2->SetZoom(GetEditorManager()->GetZoom());

    if (m_pData->m_pFileLoader)
    {
        delete m_pData->m_pFileLoader;
        m_pData->m_pFileLoader = 0;
    }

    return true;
}
