OnBnClickedApply(wxCommandEvent& WXUNUSED(evt))
{
	CPath fileName = CPath(CastChild(IDC_FILENAME, wxTextCtrl)->GetValue());

	if (fileName.IsOk() && (fileName != m_file->GetFileName())) {
		if (theApp->sharedfiles->RenameFile(m_file, fileName)) {
			FindWindow(IDC_FNAME)->SetLabel(MakeStringEscaped(m_file->GetFileName().GetPrintable()));
			FindWindow(IDC_METFILE)->SetLabel(m_file->GetFullName().GetPrintable());

			resetValueForFilenameTextEdit();

			Layout();
		}
	}
}
