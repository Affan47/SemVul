RawCommand(const wxString& command)
{
	wxASSERT(command != _T(""));

	m_pCurOpData = new CRawCommandOpData(command);

	return SendNextCommand();
}
