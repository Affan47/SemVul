bIsOkViewer( PrcBase * poPrcViewer )
{
  wxString  os1;


  if( ! poPrcViewer->bBinExists( ) )
  {
    os1 << wxT("Can't find ") << poPrcViewer->roGetBinary( ).GetFullName( )
        << wxT(" which is required to plot simulation results.\n")
        << wxT("There is no path to it or it has not been installed.\n\n");
    DlgErrMsg( wxT("Configuration Fault"), os1 );

    return( FALSE );
  }

  return( TRUE );
}
