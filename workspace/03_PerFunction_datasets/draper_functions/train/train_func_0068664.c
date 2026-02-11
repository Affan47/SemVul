OnNo( wxCommandEvent &WXUNUSED(event) )
{
  try
  {
    CMD_inquire::Instance()->ProcessYN( wxT("NO") );
  }
  catch ( ECommandError const &e )
  {
    ExGlobals::StopAllScripts();
    wxMessageDialog *md =
        new wxMessageDialog( (wxWindow*)this,
                             wxString(e.what(),wxConvUTF8),
                             wxT("Fatal error"), wxOK|wxICON_ERROR );
    md->ShowModal();
  }
  Close();
}
