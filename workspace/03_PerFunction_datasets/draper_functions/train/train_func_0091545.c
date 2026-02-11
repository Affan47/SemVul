FailedTransfer()
{
	m_inTransfer = false;

	if (!m_loaded)
		return;

	if (m_localFile != _T(""))
	{
		wxLogNull log;
		wxRemoveFile(m_localFile);
	}

	if (!m_currentPage)
		XRCCTRL(*this, "ID_FAILURE", wxStaticText)->SetLabel(_("Failed to check for newer version of FileZilla."));
	else
		XRCCTRL(*this, "ID_FAILURE", wxStaticText)->SetLabel(_("Failed to download the latest version of FileZilla."));

	((wxWizardPageSimple*)GetCurrentPage())->SetNext(m_pages[3]);
	m_pages[3]->SetPrev((wxWizardPageSimple*)GetCurrentPage());

	m_skipPageChanging = true;
	ShowPage(m_pages[3]);
	m_currentPage = 3;
	m_skipPageChanging = false;

	wxButton* pNext = wxDynamicCast(FindWindow(wxID_FORWARD), wxButton);
	pNext->Enable();
	wxButton* pPrev = wxDynamicCast(FindWindow(wxID_BACKWARD), wxButton);
	pPrev->Disable();

	XRCCTRL(*this, "ID_LOG", wxTextCtrl)->ChangeValue(m_update_log);
}
