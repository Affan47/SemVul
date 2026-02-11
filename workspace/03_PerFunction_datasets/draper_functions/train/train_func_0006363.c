OnFinish(wxWizardEvent& event)
{
	if (m_testResult != successful)
	{
		if (wxMessageBox(_("The test did not succeed. Do you really want to save the settings?"), _("Save settings?"), wxYES_NO | wxICON_QUESTION) != wxYES)
			return;
	}

	m_pOptions->SetOption(OPTION_USEPASV, XRCCTRL(*this, "ID_PASSIVE", wxRadioButton)->GetValue() ? 1 : 0);
	m_pOptions->SetOption(OPTION_ALLOW_TRANSFERMODEFALLBACK, XRCCTRL(*this, "ID_FALLBACK", wxCheckBox)->GetValue() ? 1 : 0);

	m_pOptions->SetOption(OPTION_PASVREPLYFALLBACKMODE, XRCCTRL(*this, "ID_PASSIVE_FALLBACK1", wxRadioButton)->GetValue() ? 0 : 1);

	if (XRCCTRL(*this, "ID_ACTIVEMODE1", wxRadioButton)->GetValue())
		m_pOptions->SetOption(OPTION_EXTERNALIPMODE, 0);
	else
		m_pOptions->SetOption(OPTION_EXTERNALIPMODE, XRCCTRL(*this, "ID_ACTIVEMODE2", wxRadioButton)->GetValue() ? 1 : 2);

	m_pOptions->SetOption(OPTION_LIMITPORTS, XRCCTRL(*this, "ID_ACTIVE_PORTMODE1", wxRadioButton)->GetValue() ? 0 : 1);

	long tmp;
	XRCCTRL(*this, "ID_ACTIVE_PORTMIN", wxTextCtrl)->GetValue().ToLong(&tmp); m_pOptions->SetOption(OPTION_LIMITPORTS_LOW, tmp);
	XRCCTRL(*this, "ID_ACTIVE_PORTMAX", wxTextCtrl)->GetValue().ToLong(&tmp); m_pOptions->SetOption(OPTION_LIMITPORTS_HIGH, tmp);

	m_pOptions->SetOption(OPTION_EXTERNALIP, XRCCTRL(*this, "ID_ACTIVEIP", wxTextCtrl)->GetValue());
	m_pOptions->SetOption(OPTION_EXTERNALIPRESOLVER, XRCCTRL(*this, "ID_ACTIVERESOLVER", wxTextCtrl)->GetValue());
	m_pOptions->SetOption(OPTION_NOEXTERNALONLOCAL, XRCCTRL(*this, "ID_NOEXTERNALONLOCAL", wxCheckBox)->GetValue());
}
