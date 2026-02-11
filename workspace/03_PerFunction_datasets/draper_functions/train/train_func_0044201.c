OnBrowse(wxCommandEvent& event)
{
	wxFileDialog dlg(this, _("Log file"), _T(""), _T("filezilla.log"), _T("Log files (*.log)|*.log"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (dlg.ShowModal() != wxID_OK)
		return;

	XRCCTRL(*this, "ID_FILENAME", wxTextCtrl)->ChangeValue(dlg.GetPath());
}
