bLoad( SimnNgSpice & roSimn )
{
  bool  bRtn=TRUE;


  PnlAnaBase::LoadSrcNames( roSimn.m_oaCpnts, wxT("VIR") );


  if( ! roSimn.m_oCmdDC.bIsValid( ) )                        return( FALSE );


  PnlAnaBase::bSetSrcCpnt( roSimn.m_oCpntSwpSrc );
  InitSwpUnits( );


  if( ! m_oPnlStart.bSetValue( roSimn.m_oCmdDC.m_osStart ) ) bRtn = FALSE;
  if( ! m_oPnlStop .bSetValue( roSimn.m_oCmdDC.m_osStop  ) ) bRtn = FALSE;
  if( ! m_oPnlStep .bSetValue( roSimn.m_oCmdDC.m_osStep  ) ) bRtn = FALSE;
  if( m_oPnlStart.dfGetValue( ) == 0.0 )
        m_oPnlStart.bSetUnits( m_oPnlStop.rosGetUnits( ) );


  if( roSimn.m_oCmdDC.m_osSource == wxT("TEMP") )
       m_oRbxSwpType.SetSelection( eSWP_TEMP );
  else m_oRbxSwpType.SetSelection( eSWP_CPNT );
  InitSwpType( );


  if( ! m_oPnlTemp.bSetValue( roSimn.m_oCmdOPT.m_osTEMP ) )  bRtn = FALSE;

  return( bRtn );
}
