OnSimCreate( wxCommandEvent & roEvtCmd )
{
  TextCtrl * poTxtCtl;
  wxString   os1;

  ::wxBeginBusyCursor( );

  if( ! m_oNetLst.m_osaNetLst.IsEmpty( ) )
  {
    if( bSimnSave( ) )
    {

      m_oNbkTxtCtls.bSetPage( NbkTxtCtls::ePAGE_SIMULTN );
      poTxtCtl = m_oNbkTxtCtls.poGetPage( NbkTxtCtls::ePAGE_SIMULTN );
      poTxtCtl->bLoadFile( m_poSimn->roGetSaveFile( ).GetFullPath( ) );
      poTxtCtl->SetEditable( TRUE );
    }
    else
    {
      if(      ! m_poNbkSimEng->bIsOk( ) ) os1 = m_poNbkSimEng->rosGetErrMsg();
      else if( ! m_poSimn->bIsValid( )   ) os1 = m_poSimn     ->rosGetErrMsg();
      else                                 os1 = wxT("Unknown error.");
      DlgErrMsg( wxT("Create Simulation Error"), os1 );
    }
  }
  else
  {
    os1 = wxT("There is no netlist loaded.");
    DlgErrMsg( wxT("Create Simulation Error"), os1 );
  }

  ::wxEndBusyCursor( );


  if( os1.IsEmpty( ) ) os1 = wxT(" Simulation created successfully");
  else                 os1 = wxT(" Error/s encountered creating simulation");
  SetStatusText( os1, ePANE_MESG );
}
