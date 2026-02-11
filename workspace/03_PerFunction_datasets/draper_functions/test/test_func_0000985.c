OnApply( wxCommandEvent &WXUNUSED(event) )
{
  wxString fileName( topPanel_->GetSelection() );
  if( fileName.empty() )
  {
    wxMessageDialog *md =
      new wxMessageDialog( this, wxT("no file has been chosen"),
                           wxT("Fatal error: nothing was written"), wxOK|wxICON_INFORMATION );
    md->ShowModal();
    return;
  }
  CMD_write *writeCommand = CMD_write::Instance();
  writeCommand->SetFilename( fileName );
  std::ofstream *outStream = writeCommand->GetStream();
  if( outStream->is_open() )outStream->close();
  outStream->clear( std::ios::goodbit );
  if( append_->IsChecked() )outStream->open( fileName.mb_str(wxConvUTF8), std::ios::out|std::ios::app );
  else                      outStream->open( fileName.mb_str(wxConvUTF8), std::ios::out );
  if( !outStream->is_open() )
  {
    outStream->clear( std::ios::goodbit );
    wxMessageDialog *md = new wxMessageDialog( this, wxString(wxT("Could not open "))+fileName,
                                               wxT("Fatal error: nothing was written"), wxOK|wxICON_ERROR );
    md->ShowModal();
    return;
  }
  std::vector<double> data;
  int count = variableList_->GetCount();
  for( int i=0; i<count; ++i )
  {
    if( !variableList_->IsChecked(i) )continue;
    int ndm;
    double value;
    int dimSizes[3];
    std::vector<double>().swap( data );
    wxString name( variableList_->GetString(i) );
    try
    {
      NumericVariable::GetVariable( name, ndm, value, data, dimSizes );
    }
    catch( EVariableError const &e )
    {
      outStream->close();
      wxMessageDialog *md = new wxMessageDialog( this, wxString(e.what(),wxConvUTF8),
                                                 wxString(wxT("Fatal error: matrix "))+name+wxT(" was not written"),
                                                 wxOK|wxICON_ERROR );
      md->ShowModal();
      return;
    }
    for( int j=0; j<dimSizes[0]; ++j )
    {
      for( int k=0; k<dimSizes[1]; ++k )(*outStream) << data[j+k*dimSizes[0]] << " ";
      (*outStream) << "\n";
    }
  }
  outStream->close();
}
