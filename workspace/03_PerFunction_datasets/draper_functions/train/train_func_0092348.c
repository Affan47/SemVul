OnMouseRightDown( wxMouseEvent &event )
{
  event.Skip();
  wxFileDialog *fd;
  std::ios_base::openmode mode;
  fd = new wxFileDialog( this, wxT("Save command history"), wxT(""), wxT(""),
                         wxT("Text files (*.txt)|*.txt|Any file (*.*)|*.*"),
                         wxSAVE|wxOVERWRITE_PROMPT|wxCHANGE_DIR );
  mode = std::ios_base::out;
  wxString filename;
  if( fd->ShowModal() == wxID_OK )filename = fd->GetPath();
  if( filename.empty() )return;
  std::ofstream f( filename.mb_str(wxConvUTF8), mode );
  if( !f.is_open() )
  {
    wxMessageDialog *md = new wxMessageDialog( this, wxString()<<wxT("could not open ")<<filename,
                                               wxT("Fatal error"), wxOK|wxICON_ERROR );
    md->ShowModal();
    return;
  }
  f << GetValue().mb_str(wxConvUTF8);
  f.close();
}
