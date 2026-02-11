bSave( SimnBase & roSimn )
{
  wxString  os1;


  if( roSimn.eGetSimEng( ) != eSIMR_NGSPICE ) return( FALSE );

  SimnNgSpice & roSimnNgs = (SimnNgSpice &) roSimn;


  NbkSimrBase::m_osErrMsg.Empty( );


  switch( GetSelection( ) )
  {
    case 0 :
      if( ! m_poPnlNgSpiceDC->bSave( roSimnNgs ) )
        SetErrMsg( m_poPnlNgSpiceDC->rosGetErrMsg( ) );
      break;

    case 1 :
      if( ! m_poPnlNgSpiceAC->bSave( roSimnNgs ) )
        SetErrMsg( m_poPnlNgSpiceAC->rosGetErrMsg( ) );
      break;

    case 2 :
      if( ! m_poPnlNgSpiceTR->bSave( roSimnNgs ) )
        SetErrMsg( m_poPnlNgSpiceTR->rosGetErrMsg( ) );
      break;

    default :                                 return( FALSE );
  }
  if( ! bIsOk( ) )                            return( FALSE );


  os1 = roSimnNgs.m_oCmdOPT.m_osTEMP;
  m_oDlgCfgOPT.bGetValues( roSimnNgs.m_oCmdOPT );
  roSimnNgs.m_oCmdOPT.m_osTEMP = os1;
  roSimnNgs.m_oCmdOPT.bSetWidth( roSimnNgs.m_oCmdPR.iGetParaCnt( ) );
  roSimnNgs.m_oCmdOPT.bFormat( );
  if( ! roSimnNgs.m_oCmdOPT.bIsValid( ) )
  {
    os1 = wxT("OPTIONS command fault :\n\n  ");
    SetErrMsg( os1 + roSimnNgs.m_oCmdOPT.rosGetErrMsg( ) );
    return( FALSE );
  }

  return( TRUE );
}
