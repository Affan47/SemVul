bSetGuileProc( const wxString & rosPName )
{
  if( ! m_oPrcGNetList.bSetGuileProc( rosPName ) ) return( FALSE );


  m_poCfg->SetPath( wxT("/gNetList") );
  m_poCfg->Write( wxT("GuileProc"), rosGetGuileProc( ) );


  m_poCfg->Flush( );

  return( TRUE );
}
