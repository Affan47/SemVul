SetEditorStyleBeforeFileOpen()
{
    ConfigManager* mgr = Manager::Get()->GetConfigManager(_T("editor"));


    if (m_pProjectFile)
    {
        if (mgr->ReadBool(_T("/tab_text_relative"), true))
            m_Shortname = m_pProjectFile->relativeToCommonTopLevelPath;
        else
            m_Shortname = m_pProjectFile->file.GetFullName();
        SetEditorTitle(m_Shortname);
    }


    m_pData->mFoldingLimit = mgr->ReadBool(_T("/folding/limit"), false);
    m_pData->mFoldingLimitLevel = mgr->ReadInt(_T("/folding/limit_level"), 1);


    m_pData->m_strip_trailing_spaces = mgr->ReadBool(_T("/eol/strip_trailing_spaces"), true);
    m_pData->m_ensure_final_line_end = mgr->ReadBool(_T("/eol/ensure_final_line_end"), true);
    m_pData->m_ensure_consistent_line_ends = mgr->ReadBool(_T("/eol/ensure_consistent_line_ends"), false);

    InternalSetEditorStyleBeforeFileOpen(m_pControl);

    SetFoldingIndicator(mgr->ReadInt(_T("/folding/indicator"), 2));
    UnderlineFoldedLines(mgr->ReadBool(_T("/folding/underline_folded_line"), true));

    if (m_pControl2)
        InternalSetEditorStyleBeforeFileOpen(m_pControl2);

    SetLanguage( HL_AUTO );
}
