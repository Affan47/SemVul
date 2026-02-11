Load()
{
	if (!Create(m_parent, wxID_ANY, _("Check for updates"), wxNullBitmap, wxPoint(0, 0)))
		return false;

	wxSize minPageSize = GetPageAreaSizer()->GetMinSize();

	for (int i = 1; i <= 5; i++)
	{
		wxWizardPageSimple* page = new wxWizardPageSimple();
		bool res = wxXmlResource::Get()->LoadPanel(page, this, wxString::Format(_T("ID_CHECKFORUPDATE%d"), i));
		if (!res)
		{
			delete page;
			return false;
		}
		page->Show(false);

		m_pages.push_back(page);
	}
	for (unsigned int i = 0; i < (m_pages.size() - 1); i++)
		m_pages[i]->Chain(m_pages[i], m_pages[i + 1]);


	GetPageAreaSizer()->Add(m_pages[0]);

	std::vector<wxWindow*> windows;
	for (unsigned int i = 0; i < m_pages.size(); i++)
		windows.push_back(m_pages[i]);

	wxGetApp().GetWrapEngine()->WrapRecursive(windows, 1.7, "UpdateCheck", wxSize(), minPageSize);

	XRCCTRL(*this, "ID_CHECKINGTEXT", wxStaticText)->Hide();
	XRCCTRL(*this, "ID_CHECKINGPROGRESS", wxGauge)->Hide();
	XRCCTRL(*this, "ID_CHECKINGTEXTPROGRESS", wxStaticText)->Hide();

	XRCCTRL(*this, "ID_CHECKINGPROGRESS", wxGauge)->SetRange(MAXCHECKPROGRESS);

	GetPageAreaSizer()->Add(m_pages[1]);
	m_pages[1]->SetPrev(0);
	for (int i = 2; i <= 4; i++)
	{
		m_pages[i]->SetPrev(0);
		m_pages[i]->SetNext(0);
		GetPageAreaSizer()->Add(m_pages[i]);
	}

	if (COptions::Get()->GetOptionVal(OPTION_UPDATECHECK_CHECKBETA) != 0)
		XRCCTRL(*this, "ID_CHECKBETA", wxCheckBox)->SetValue(1);
	else
		XRCCTRL(*this, "ID_CHECKBETA", wxCheckBox)->SetValue(0);

	m_loaded = true;

	CenterOnParent();

	return true;
}
