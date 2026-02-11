OnThemeChange(wxCommandEvent& event)
{
	wxChoice* pTheme = XRCCTRL(*this, "ID_THEME", wxChoice);

	const int sel = pTheme->GetSelection();
	const wxString theme = ((wxStringClientData*)pTheme->GetClientObject(sel))->GetData();

	DisplayTheme(theme);
}
