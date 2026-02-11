resetValueForFilenameTextEdit()
{
	CastChild(IDC_FILENAME, wxTextCtrl)->SetValue(m_file->GetFileName().GetPrintable());
	m_filenameChanged = false;
	setEnableForApplyButton();
}
