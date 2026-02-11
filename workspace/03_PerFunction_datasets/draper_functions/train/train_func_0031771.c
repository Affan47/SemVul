SavePage()
{
	SetOptionFromCheck(XRCID("ID_ASCIIWITHOUT"), OPTION_ASCIINOEXT);
	SetOptionFromCheck(XRCID("ID_ASCIIDOTFILE"), OPTION_ASCIIDOTFILE);

	int mode;
	if (GetRCheck(XRCID("ID_TYPE_ASCII")))
		mode = 1;
	else if (GetRCheck(XRCID("ID_TYPE_BINARY")))
		mode = 2;
	else
		mode = 0;
	m_pOptions->SetOption(OPTION_ASCIIBINARY, mode);

	const wxListCtrl* pListCtrl = XRCCTRL(*this, "ID_EXTENSIONS", wxListCtrl);
	wxASSERT(pListCtrl);

	wxString extensions;

	for (int i = 0; i < pListCtrl->GetItemCount(); i++)
	{
		wxString ext = pListCtrl->GetItemText(i);
		ext.Replace(_T("\\"), _T("\\\\"));
		ext.Replace(_T("|"), _T("\\|"));
		if (extensions != _T(""))
			extensions += _T("|");
		extensions += ext;
	}
	m_pOptions->SetOption(OPTION_ASCIIFILES, extensions);

	return true;
}
