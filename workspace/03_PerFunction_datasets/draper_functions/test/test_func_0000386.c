bOpen( void )
{
  bool  bRtn=TRUE;


  if(      m_poFrmMain->m_oSimnNgs.bLoadFile( ) )
    m_poFrmMain->m_oSimnGcp = m_poFrmMain->m_oSimnNgs;
  else if( m_poFrmMain->m_oSimnGcp.bLoadFile( ) )
    m_poFrmMain->m_oSimnNgs = m_poFrmMain->m_oSimnGcp;


  if( ! m_poFrmMain->m_oNetLst.bIsValid( ) )
  {
    DlgErrNetLst( );
    m_poFrmMain->m_oNbkTxtCtls.bSetPage( NbkTxtCtls::ePAGE_NETLIST );
    bRtn = FALSE;
  }
  else
    m_poFrmMain->SetStatusText( wxT(" Netlist file opened successfully"),
                                FrmMain::ePANE_MESG );


  bSetTitle( );
  bSetSchemFiles( m_poFrmMain->m_oNetLst.rosGetSchemFiles( ) );

  return( bRtn );
}
