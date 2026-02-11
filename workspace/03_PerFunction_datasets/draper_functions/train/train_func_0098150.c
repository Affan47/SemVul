OnImportPNG( wxCommandEvent &WXUNUSED(event) )
{
  wxString wildcard( wxT("PNG (*.png)|*.png") );
  wxFileDialog *fd = new wxFileDialog( this, wxT("Choose a PNG file"), wxT(""), wxT(""),
                                       wildcard,
                                       wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR|wxFD_PREVIEW );
  if( fd->ShowModal() != wxID_OK )return;
  wxString filename( fd->GetFilename() );
  if( filename.empty() )return;


  wxImage image( filename, wxBITMAP_TYPE_PNG );
  ImportForm *importForm = new ImportForm( this, image );
}
