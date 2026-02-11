OnSelSimEng( wxCommandEvent & roEvtCmd )
{
  int  iw, ih;


  GetClientSize( &iw, &ih );


  ::wxBeginBusyCursor( );
  Show( FALSE );


  wxProgressDialog  oDlgProgress( wxT(" GNU Spice GUI"),
                             wxT("Changing simulation engines ..."), 100, this,
                             wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_SMOOTH );
  oDlgProgress.CenterOnParent( );
  oDlgProgress.Update( 0 ); ::wxMilliSleep( 50 );


  m_poCfg->SetPath( wxT("/Simulator") );
  if( GetMenuBar( )->IsChecked( ID_MNU_GNUCAP ) )
       m_poCfg->Write( wxT("Engine"), CLP_GNUCAP  );
  else m_poCfg->Write( wxT("Engine"), CLP_NGSPICE );
  m_poCfg->Flush( );


  oDlgProgress.Update( 10 );


  InitSimEng( );


  oDlgProgress.Update( 50 ); ::wxMilliSleep( 50 );


  InitLogFiles( );


  oDlgProgress.Update( 60 ); ::wxMilliSleep( 50 );


  DoLayout( );


  oDlgProgress.Update( 70 ); ::wxMilliSleep( 50 );


  if( ! m_oNetLst.bIsEmpty( ) )
  {
    if( GetMenuBar( )->IsChecked( ID_MNU_GNUCAP ) ) m_oSimnGcp = m_oSimnNgs;
    else                                            m_oSimnNgs = m_oSimnGcp;
  }


  oDlgProgress.Update( 80 ); ::wxMilliSleep( 50 );


  m_poNbkSimEng->bLoad( *m_poSimn );


  oDlgProgress.Update( 90 ); ::wxMilliSleep( 50 );


  SetClientSize( iw, ih );


  oDlgProgress.Update( 99 ); ::wxMilliSleep( 50 );
  oDlgProgress.Update( 100 );


  Show( TRUE );
  ::wxEndBusyCursor( );
}
