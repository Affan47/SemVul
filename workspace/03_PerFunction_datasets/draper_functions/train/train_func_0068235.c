Close(wxCommandEvent& WXUNUSED(event))
{
	if (theApp->amuledlg->IsEnabled()) {
		theApp->amuledlg->Close();
	}
}
