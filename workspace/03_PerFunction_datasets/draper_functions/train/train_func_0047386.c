ManUser( void )
{
  wxFileName  ofn1, ofn2;
  wxString    os1;


  if( m_oHtmlWin.GetOpenedPage( ).IsEmpty( ) )
  {

    os1 = rosGetInstallPath( );
    if( os1.IsEmpty( ) ) return;
    ofn1 = os1 + wxT("/share/doc/gspiceui/html/User-Manual.html");
    ofn2 = os1 + wxT("/html/User-Manual.html");


    if(      ofn1.FileExists( ) ) os1 = ofn1.GetFullPath( );
    else if( ofn2.FileExists( ) ) os1 = ofn2.GetFullPath( );
    else
    {

      os1.Empty( );
      os1 << wxT("\nThe base manual page \"") << ofn1.GetFullName( ) << wxT('\"')
          << wxT(" couldn't be found in either of the following locations :\n\n")
          << wxT("     ") << ofn1.GetPath( ) << wxT("/\n")
          << wxT("     ") << ofn2.GetPath( ) << wxT("/\n");
      wxMessageBox( os1, wxT("User Manual"), wxOK | wxCENTRE, m_poFrmMain );
      return;
    }


    m_oHtmlWin.LoadPage( os1 );
    SetTitle( );
  }


  Show( TRUE );
}
