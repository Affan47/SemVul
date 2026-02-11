AddSlider(const wxString &Prompt, int pos, int Max, int Min)
{
   UseUpId();
   if( mShuttleMode != eIsCreating )
      return wxDynamicCast(wxWindow::FindWindowById( miId, mpDlg), wxSlider);
   AddPrompt( Prompt );
   wxSlider * pSlider;
   mpWind = pSlider = new wxSlider( mpParent, miId,
      pos, Min, Max,
      wxDefaultPosition, wxDefaultSize,
      Style( wxSL_HORIZONTAL | wxSL_LABELS | wxSL_AUTOTICKS )
      );
   mpWind->SetName(wxStripMenuCodes(Prompt));
   miProp=1;
   UpdateSizers();
   return pSlider;
}
