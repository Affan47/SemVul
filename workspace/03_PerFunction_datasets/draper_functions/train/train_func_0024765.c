onBrowseOverrideDinkrefDir(wxCommandEvent& aEvent)
{
  const wxString& dir = wxDirSelector(_("Choose the Dink Smallwood install directory"),
				      mOverrideDinkrefDirBox->GetValue());
  if (!dir.IsEmpty())
    mOverrideDinkrefDirBox->SetValue(dir);
}
