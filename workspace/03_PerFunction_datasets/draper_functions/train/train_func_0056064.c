OnPageChanged( wxWizardExEvent& event ) {
    if (event.GetDirection() == false) return;
    wxLogTrace(wxT("Function Start/End"), wxT("CWelcomePage::OnPageChanged - Function Begin"));

    CMainDocument*         pDoc = wxGetApp().GetDocument();
    ACCT_MGR_INFO          ami;
    bool                   is_acct_mgr_detected = false;
    bool                   is_wcg_client = isWCGClient();
    wxString               strBuffer = wxEmptyString;

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));
    wxASSERT(m_pTitleStaticCtrl);
    wxASSERT(m_pDescriptionStaticCtrl);
    wxASSERT(m_pAttachToProjectCtrl);
    wxASSERT(m_pAttachToAccountManagerCtrl);
    wxASSERT(m_pDirectionsStaticCtrl);
    wxASSERT(m_pChangeApplicationsCtrl);

	if ( !is_wcg_client ) {
		m_pTitleStaticCtrl->SetLabel(
			_("Add project or account manager")
		);
	} else {
		m_pTitleStaticCtrl->SetLabel(
			_("Add project or use BOINC Account Manager")
		);
	}

    pDoc->rpc.acct_mgr_info(ami);
    is_acct_mgr_detected = ami.acct_mgr_url.size() ? true : false;

    if (is_acct_mgr_detected) {
        strBuffer.Printf(
            _("If possible, add projects at the\n%s web site.\n\nProjects added via this wizard will not be\nlisted on or managed via %s."),
            wxString(ami.acct_mgr_name.c_str(), wxConvUTF8).c_str(),
            wxString(ami.acct_mgr_name.c_str(), wxConvUTF8).c_str()
        );

        m_pDescriptionStaticCtrl->SetLabel(
            strBuffer
        );

		m_pAttachToAccountManagerCtrl->SetLabel(
			_("Use account manager")
		);
        m_pAttachToAccountManagerCtrl->Disable();
    } else {
        if (!is_wcg_client) {
            m_pDescriptionStaticCtrl->SetLabel(
_("There are over 30 BOINC-based projects\n\
doing research in many areas of science,\n\
and you can volunteer for as many of them as you like.\n\
You can add a project directly,\n\
or use an 'Account Manager' web site to select projects.")
            );

			m_pAttachToAccountManagerCtrl->SetLabel(
				_("Use account manager")
			);
        } else {
            m_pDescriptionStaticCtrl->SetLabel(
_("You have chosen to add a new volunteer computing project or change which projects\n\
you contribute to.\n\
\n\
Some of these projects are run and managed by World Community Grid, while others\n\
are run and managed by other researchers or organizations. The BOINC software\n\
can divide your spare processing power among any combination of projects.\n\
\n\
Alternatively, if you have registered with a BOINC Account Manager, you can use\n\
this to choose which projects to support.\n\
\n\
Please choose which type of change you would like to make:\n")
            );

			m_pAttachToAccountManagerCtrl->SetLabel(
				_("Use a BOINC Account Manager")
			);
        }

		m_pAttachToAccountManagerCtrl->Enable();
    }

    if (!is_wcg_client) {
		m_pAttachToProjectCtrl->SetLabel(
			_("Add project")
		);

        m_pDirectionsStaticCtrl->SetLabel(
            _("To continue, click Next.")
        );

        m_pChangeApplicationsCtrl->Hide();
	} else {
        m_pChangeApplicationsCtrl->SetLabel(
			 _("Add or change your World Community Grid projects")
        );
		m_pAttachToProjectCtrl->SetLabel(
			_("Add projects run by other researchers or organizations")
		);
	}

    Fit();
    wxLogTrace(wxT("Function Start/End"), wxT("CWelcomePage::OnPageChanged - Function End"));
}
