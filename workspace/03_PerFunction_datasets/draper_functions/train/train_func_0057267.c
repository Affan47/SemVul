UpdateControls() {
    unsigned int        i;
    unsigned int        j;
    bool                bCreateMainSizer = false;
    CTaskItemGroup*     pGroup = NULL;
    CTaskItem*          pItem = NULL;


    bCreateMainSizer = !GetSizer();
    if (bCreateMainSizer) {
        SetAutoLayout(TRUE);
        m_pSizer = new wxBoxSizer( wxVERTICAL  );
        m_pSizer->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    }


    for (i=0; i < m_pParent->m_TaskGroups.size(); i++) {
        pGroup = m_pParent->m_TaskGroups[i];
        if (!pGroup->m_pStaticBoxSizer) {
            pGroup->m_pStaticBox = new wxStaticBox(this, wxID_ANY, pGroup->m_strName);
            pGroup->m_pStaticBoxSizer = new wxStaticBoxSizer(pGroup->m_pStaticBox, wxVERTICAL);
            m_pSizer->Add(pGroup->m_pStaticBoxSizer, 0, wxEXPAND|wxALL, 5);
#ifdef __WXMAC__
            pGroup->SetupMacAccessibilitySupport();
#endif
        }
    }


    for (i=0; i < m_pParent->m_TaskGroups.size(); i++) {
        pGroup = m_pParent->m_TaskGroups[i];
        for (j=0; j < pGroup->m_Tasks.size(); j++) {
            pItem = pGroup->m_Tasks[j];
            if (!pItem->m_pButton) {
                pItem->m_pButton = new wxButton;
                pItem->m_strNameEllipsed = pItem->m_strName;
                EllipseStringIfNeeded(pItem->m_strNameEllipsed);
                pItem->m_pButton->Create(this, pItem->m_iEventID, pItem->m_strNameEllipsed, wxDefaultPosition, wxSize(TASKBUTTONWIDTH, -1), 0);
                pItem->m_pButton->SetHelpText(pItem->m_strDescription);
#if wxUSE_TOOLTIPS
                pItem->m_pButton->SetToolTip(pItem->m_strDescription);
#endif
                pGroup->m_pStaticBoxSizer->Add(pItem->m_pButton, 0, wxEXPAND|wxALL, 5);
            }
        }
    }

    if (bCreateMainSizer) {
        SetSizer(m_pSizer);
    }


    FitInside();

    return 0;
}
