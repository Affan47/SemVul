OnWizardUpdate(wxCommandEvent& WXUNUSED(event)) {
    wxLogTrace(wxT("Function Start/End"), wxT("CAdvancedFrame::OnWizardUpdate - Function Begin"));

    CMainDocument*            pDoc = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (!pDoc->IsUserAuthorized())
        return;

    if (pDoc->IsConnected()) {

        StopTimers();

        CWizardAttach* pWizard = new CWizardAttach(this);

        pWizard->SyncToAccountManager();

        if (pWizard)
            pWizard->Destroy();

        DeleteMenu();
        CreateMenu();
        pDoc->ForceCacheUpdate();
        FireRefreshView();
        ResetReminderTimers();


        StartTimers();
    } else {
        ShowNotCurrentlyConnectedAlert();
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CAdvancedFrame::OnWizardUpdate - Function End"));
}
