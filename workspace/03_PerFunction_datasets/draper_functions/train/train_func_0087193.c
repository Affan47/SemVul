SetIntOptionFromText(int ctrlId, int optionId)
{
	const wxString& value = GetText(ctrlId);

	long n;
	wxCHECK_RET(value.ToLong(&n), _T("Some options page did not validate user input!"));

	m_pOptions->SetOption(optionId, n);
}
