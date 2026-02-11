OnBrowseEditor(wxCommandEvent& event)
{
	wxFileDialog dlg(this, _("Select default editor"), _T(""), _T(""),
#ifdef __WXMSW__
		_T("Executable file (*.exe)|*.exe"),
#elif __WXMAC__
		_T("Applications (*.app)|*.app"),
#else
		wxFileSelectorDefaultWildcardStr,
#endif
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() != wxID_OK)
		return;

	wxString editor = dlg.GetPath();
	if (editor == _T(""))
		return;

	if (!ProgramExists(editor))
	{
		XRCCTRL(*this, "ID_EDITOR", wxWindow)->SetFocus();
		wxMessageBox(_("Selected editor does not exist."), _("File not found"), wxICON_EXCLAMATION, this);
		return;
	}

	if (editor.Find(' ') != -1)
		editor = _T("\"") + editor + _T("\"");

	bool tmp;
	SetText(XRCID("ID_EDITOR"), editor, tmp);
}
