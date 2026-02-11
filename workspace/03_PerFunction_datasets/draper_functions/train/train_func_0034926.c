bReload( void )
{
  bool  bRtn;


  m_poFrmMain->m_oNbkTxtCtls.bInitialize( );


  if( ! m_oPrcGNetList.roaGetSchemFiles( ).IsEmpty( ) )
  {
    bRtn = bImport( );
    if( bRtn )
      m_poFrmMain->SetStatusText( wxT(" Schematic file/s re-imported successfully"),
                                  FrmMain::ePANE_MESG );
  }
  else if( m_oPrcGNetList.roGetNetLstFile( ).IsOk( ) )
  {
    bRtn = bOpen( );
    if( bRtn )
      m_poFrmMain->SetStatusText( wxT(" Netlist file reloaded successfully"),
                                  FrmMain::ePANE_MESG );
  }
  else
  {

    m_poFrmMain->DlgErrMsg( wxT("Reload Operation Error"),
                            wxT("No file is currently open.") );
    bRtn = FALSE;
  }

  return( bRtn );
}
