ShowDaemonStartFailedAlert() {
    CSkinAdvanced*      pSkinAdvanced = wxGetApp().GetSkinManager()->GetAdvanced();
    wxString            strDialogTitle = wxEmptyString;
    wxString            strDialogMessage = wxEmptyString;


    wxASSERT(pSkinAdvanced);
    wxASSERT(wxDynamicCast(pSkinAdvanced, CSkinAdvanced));


    wxLogTrace(wxT("Function Start/End"), wxT("CBOINCBaseFrame::ShowDaemonStartFailedAlert - Function Begin"));


    strDialogTitle.Printf(
        _("%s - Daemon Start Failed"),
        pSkinAdvanced->GetApplicationName().c_str()
    );


#ifdef __WXMSW__
    strDialogMessage.Printf(
        _("%s is not able to start a %s client.\nPlease launch the Control Panel->Administative Tools->Services applet and start the BOINC service."),
        pSkinAdvanced->GetApplicationName().c_str(),
        pSkinAdvanced->GetApplicationShortName().c_str()
    );
#else
    strDialogMessage.Printf(
        _("%s is not able to start a %s client.\nPlease start the daemon and try again."),
        pSkinAdvanced->GetApplicationName().c_str(),
        pSkinAdvanced->GetApplicationShortName().c_str()
    );
#endif

    ShowAlert(
        strDialogTitle,
        strDialogMessage,
        wxOK | wxICON_ERROR
    );

    wxLogTrace(wxT("Function Start/End"), wxT("CBOINCBaseFrame::ShowDaemonStartFailedAlert - Function End"));
}
