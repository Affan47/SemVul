_ProcessCancelEvent( wxWizardExEvent& event ) {

    bool bCancelWithoutNextPage = false;
    wxWizardPageEx* page = GetCurrentPage();

    int iRetVal = wxGetApp().SafeMessageBox(
        _("Do you really want to cancel?"),
        _("Question"),
        wxICON_QUESTION | wxYES_NO,
        this
    );


    GetNextButton()->Enable();
    GetBackButton()->Enable();


    if (wxYES == iRetVal) {
        if ((page == m_ProjectInfoPage) || (page == m_AccountManagerInfoPage)) {
            m_ProjectInfoPage->m_pProjectURLCtrl->SetValidator(wxDefaultValidator);
        } else if (page == m_AccountInfoPage) {
            m_AccountInfoPage->m_pAccountEmailAddressCtrl->SetValidator(wxDefaultValidator);
            m_AccountInfoPage->m_pAccountPasswordCtrl->SetValidator(wxDefaultValidator);
            if (IsAttachToProjectWizard) {
                m_AccountInfoPage->m_pAccountConfirmPasswordCtrl->SetValidator(wxDefaultValidator);
            }
        } else if (page == m_ErrProxyPage) {
            m_ErrProxyPage->m_pProxyHTTPServerCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxyHTTPPortCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxyHTTPUsernameCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxyHTTPPasswordCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxySOCKSServerCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxySOCKSPortCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxySOCKSUsernameCtrl->SetValidator(wxDefaultValidator);
            m_ErrProxyPage->m_pProxySOCKSPasswordCtrl->SetValidator(wxDefaultValidator);
        }
    }


    bCancelWithoutNextPage |= (page == m_ErrNotDetectedPage);
    bCancelWithoutNextPage |= (page == m_ErrUnavailablePage);
    bCancelWithoutNextPage |= (page == m_ErrNoInternetConnectionPage);

    if (IsAttachToProjectWizard) {
        bCancelWithoutNextPage |= (page == m_ErrAlreadyExistsPage);
    } else {
        bCancelWithoutNextPage |= (page == m_WelcomePage);
    }
    if (wxYES != iRetVal) {
        event.Veto();
    }
}
