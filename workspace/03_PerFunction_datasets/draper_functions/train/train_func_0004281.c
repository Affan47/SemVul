Split(cbEditor::SplitType split)
{
    Freeze();


    if (m_pSplitter)
    {
        Unsplit();
        Manager::Yield();
    }
    m_SplitType = split;
    if (m_SplitType == stNoSplit)
    {
        Thaw();
        return;
    }


    m_pSizer->Detach(m_pControl);


    m_pSplitter = new wxSplitterWindow(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER | wxSP_LIVE_UPDATE);
    m_pSplitter->SetMinimumPaneSize(32);


    m_pControl2 = CreateEditor();


    InternalSetEditorStyleBeforeFileOpen(m_pControl2);


    for (int i = 0; i < wxSCI_INDIC_MAX; ++i )
    {
        m_pControl2->IndicatorSetStyle(i, m_pControl->IndicatorGetStyle(i));
        m_pControl2->IndicatorSetUnder(i, m_pControl->IndicatorGetUnder(i));
        m_pControl2->IndicatorSetForeground(i, m_pControl->IndicatorGetForeground(i));

    }

    ConfigManager* mgr = Manager::Get()->GetConfigManager(_T("editor"));
    SetFoldingIndicator(mgr->ReadInt(_T("/folding/indicator"), 2));
    UnderlineFoldedLines(mgr->ReadBool(_T("/folding/underline_folded_line"), true));

    if (m_pTheme)
        m_pTheme->Apply(m_lang, m_pControl2);


    m_pControl2->SetDocPointer(m_pControl->GetDocPointer());


    #if defined ( __WXGTK__ ) && wxCHECK_VERSION(2, 9, 0)
    Thaw();
    #endif

    m_pControl->Reparent(m_pSplitter);
    m_pControl2->Reparent(m_pSplitter);
    #if defined ( __WXGTK__ ) && wxCHECK_VERSION(2, 9, 0)
    Freeze();
    #endif


    m_pSizer->SetDimension(0, 0, GetSize().x, GetSize().y);
    m_pSizer->Add(m_pSplitter, 1, wxEXPAND);

    m_pSizer->Layout();


    switch (m_SplitType)
    {
        case stHorizontal:
            m_pSplitter->SplitHorizontally(m_pControl, m_pControl2, 0);
            break;

        case stVertical:
            m_pSplitter->SplitVertically(m_pControl, m_pControl2, 0);
            break;

        case stNoSplit:
        default:
            break;
    }

    SetEditorStyleAfterFileOpen();


    m_pControl2->SetZoom(m_pControl->GetZoom());

    m_pControl2->SetMarginWidth(C_LINE_MARGIN, m_pControl->GetMarginWidth(C_LINE_MARGIN));

    Thaw();
}
