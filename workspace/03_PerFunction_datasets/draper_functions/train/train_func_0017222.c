FailedChecksum()
{
	m_inTransfer = false;

	if (m_localFile == _T(""))
		return;
	else
	{
		wxLogNull log;
		wxRemoveFile(m_localFile);
	}

	wxString label = _("Checksum mismatch of downloaded file.");
	XRCCTRL(*this, "ID_FAILURE", wxStaticText)->SetLabel(label);

	XRCCTRL(*this, "ID_MISMATCH1", wxStaticText)->Show();
	XRCCTRL(*this, "ID_MISMATCH2", wxStaticText)->Show();
	XRCCTRL(*this, "ID_MISMATCH3", wxStaticText)->Show();
	XRCCTRL(*this, "ID_MISMATCH4", wxStaticText)->Show();

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

	RewrapPage(3);
}
