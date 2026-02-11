OnSavePS( wxCommandEvent &WXUNUSED(event) )
{
  wxString wildcard( wxT("PostScript (*.eps)|*.eps") );
  wxFileDialog *fd = new wxFileDialog( this, wxT("Choose an output file"), wxT(""), wxT(""),
                                       wildcard, wxSAVE|wxOVERWRITE_PROMPT|wxCHANGE_DIR );
  if( fd->ShowModal() != wxID_OK )return;
  wxString filename( fd->GetFilename() );
  if( filename.empty() )return;
  if( filename.find_last_of(wxT('.')) == filename.npos )filename += wxT(".eps");
  std::ofstream outFile;
  outFile.open( filename.mb_str(wxConvUTF8), std::ios_base::out );
  if( !outFile.is_open() )
  {
    wxMessageBox( wxString(wxT("unable to open "))+filename, wxT("error"),
                  wxOK|wxICON_ERROR );
    return;
  }
  outFile.close();
  try
  {
    static_cast<GraphicsPage*>(notebook_->GetCurrentPage())->SavePS( filename );
  }
  catch ( EGraphicsError const &e )
  {
    wxMessageBox( wxString(e.what(),wxConvUTF8), wxT("error"), wxOK|wxICON_ERROR );
    return;
  }
}
