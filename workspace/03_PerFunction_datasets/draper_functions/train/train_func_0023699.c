OnAccountUseExistingCtrlSelected( wxCommandEvent& WXUNUSED(event) ) {
    CWizardAttach*         pWA = ((CWizardAttach*)GetParent());
    PROJECT_CONFIG&        pc = pWA->project_config;

    m_pAccountPasswordStaticCtrl->SetLabel(
        _("&Password:")
    );
    m_pAccountConfirmPasswordStaticCtrl->Hide();
    m_pAccountConfirmPasswordCtrl->Hide();
    m_pAccountPasswordRequirmentsStaticCtrl->Hide();

    if (pc.uses_username) {
        m_pAccountUsernameCtrl->SetFocus();
    } else {
        m_pAccountEmailAddressCtrl->SetFocus();
    }

    Fit();
}
