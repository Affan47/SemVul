bValidate( void )
{

  SimnBase::bValidate( );

  if( ! m_oCmdOPT.bIsValid( ) ) SetErrMsg( m_oCmdOPT.rosGetErrMsg( ) );
  if( ! m_oCmdPR .bIsValid( ) ) SetErrMsg( m_oCmdPR .rosGetErrMsg( ) );
  if( ! m_oCmdGEN.bIsValid( ) ) SetErrMsg( m_oCmdGEN.rosGetErrMsg( ) );

  switch( eGetAnaType( ) )
  {
    case eCMD_OP :
      if( ! m_oCmdOP.bIsValid( ) ) SetErrMsg( m_oCmdOP.rosGetErrMsg( ) );
      break;

    case eCMD_DC :
      if( ! m_oCmdDC.bIsValid( ) ) SetErrMsg( m_oCmdDC.rosGetErrMsg( ) );
      break;

    case eCMD_AC :
      if( ! m_oCmdAC.bIsValid( ) ) SetErrMsg( m_oCmdAC.rosGetErrMsg( ) );
      break;

    case eCMD_TR :
      if( ! m_oCmdTR.bIsValid( ) ) SetErrMsg( m_oCmdTR.rosGetErrMsg( ) );
      break;

    case eCMD_FO :
      if( ! m_oCmdFO.bIsValid( ) ) SetErrMsg( m_oCmdFO.rosGetErrMsg( ) );
      break;

    default :
      SetErrMsg( wxT("No valid analysis command exists.") );
  }

  return( bIsValid( ) );
}
