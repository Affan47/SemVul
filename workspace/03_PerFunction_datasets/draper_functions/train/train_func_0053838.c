OnProjectsAttachToProject() {
    wxLogTrace(wxT("Function Start/End"), wxT("CSimpleFrame::OnProjectsAttachToProject - Function Begin"));

    CMainDocument* pDoc     = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (!pDoc->IsUserAuthorized())
        return;

    if (pDoc->IsConnected()) {

        CWizardAttach* pWizard = new CWizardAttach(this);

        wxString strName = wxEmptyString;
        wxString strURL = wxEmptyString;
        wxString strTeamName = wxEmptyString;
        pWizard->Run( strName, strURL, strTeamName, false );

        if (pWizard)
            pWizard->Destroy();

    } else {
        ShowNotCurrentlyConnectedAlert();
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CSimpleFrame::OnProjectsAttachToProject - Function End"));
}
