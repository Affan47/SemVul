OnBnClickedClear(wxCommandEvent& WXUNUSED(evt))
{
	CastChild(IDC_CMT_TEXT, wxTextCtrl)->SetValue(wxEmptyString);
}
