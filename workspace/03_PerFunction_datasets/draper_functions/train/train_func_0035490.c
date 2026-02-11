CreateControls()
{
    CSkinAdvanced*     pSkinAdvanced = wxGetApp().GetSkinManager()->GetAdvanced();

    wxASSERT(pSkinAdvanced);
    wxASSERT(wxDynamicCast(pSkinAdvanced, CSkinAdvanced));

    wxFlexGridSizer* itemFlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
    itemFlexGridSizer2->AddGrowableRow(0);
    itemFlexGridSizer2->AddGrowableCol(0);
    SetSizer(itemFlexGridSizer2);

    m_pList = new CDlgEventLogListCtrl(this, ID_SIMPLE_MESSAGESVIEW, EVENT_LOG_DEFAULT_LIST_MULTI_SEL_FLAGS);
    itemFlexGridSizer2->Add(m_pList, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);

    itemFlexGridSizer2->Add(itemBoxSizer4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 12);

    m_pFilterButton = new wxButton(this, ID_TASK_MESSAGES_FILTERBYPROJECT, _("&Show only this project"),  wxDefaultPosition, wxDefaultSize);
    itemBoxSizer4->Add(m_pFilterButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#ifdef wxUSE_CLIPBOARD
    wxButton* itemButton1 = new wxButton(this, ID_COPYAll, _("Copy &All"), wxDefaultPosition, wxDefaultSize );
    itemButton1->SetHelpText(
        _("Copy all the messages to the clipboard.")
    );
#if wxUSE_TOOLTIPS
    itemButton1->SetToolTip(
        _("Copy all the messages to the clipboard.")
    );
#endif
    itemBoxSizer4->Add(itemButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pCopySelectedButton = new wxButton(this, ID_COPYSELECTED, _("Copy &Selected"),  wxDefaultPosition, wxDefaultSize );
    m_pCopySelectedButton->SetHelpText(
#ifdef __WXMAC__
        _("Copy the selected messages to the clipboard. You can select multiple messages by holding down the shift or command key while clicking on messages.")
#else
        _("Copy the selected messages to the clipboard. You can select multiple messages by holding down the shift or control key while clicking on messages.")
#endif
    );
#if wxUSE_TOOLTIPS
    m_pCopySelectedButton->SetToolTip(
#ifdef __WXMAC__
        _("Copy the selected messages to the clipboard. You can select multiple messages by holding down the shift or command key while clicking on messages.")
#else
        _("Copy the selected messages to the clipboard. You can select multiple messages by holding down the shift or control key while clicking on messages.")
#endif
    );
#endif
    itemBoxSizer4->Add(m_pCopySelectedButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

    wxButton* itemButton44 = new wxButton(this, wxID_OK, _("&Close"),  wxDefaultPosition, wxDefaultSize);
    itemBoxSizer4->Add(itemButton44, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#ifndef __WXMAC__
    wxContextHelpButton* itemButton45 = new wxContextHelpButton(this);
    itemBoxSizer4->Add(itemButton45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#else
	wxButton* itemButton45 = new wxButton(this, ID_SIMPLE_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize);
    wxString helpTip;
    helpTip.Printf(_("Get help with %s"), pSkinAdvanced->GetApplicationShortName().c_str());
    itemButton45->SetHelpText(helpTip);
#ifdef wxUSE_TOOLTIPS
	itemButton45->SetToolTip(helpTip);
#endif
    itemBoxSizer4->Add(itemButton45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

    SetFilterButtonText();
}
