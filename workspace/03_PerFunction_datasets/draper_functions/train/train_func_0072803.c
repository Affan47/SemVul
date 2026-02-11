bValidate( void )
{
  double  df1;
  long    li1;

  CmdBase::bValidate( );

  if( ! ConvertType::bStrToDFlt( m_osABSTOL, &df1 ) )
    SetErrMsg( wxT("Invalid value for ABSTOL.") );

  if( ! ConvertType::bStrToDFlt( m_osCHGTOL, &df1 ) )
    SetErrMsg( wxT("Invalid value for CHGTOL.") );

  if( ! ConvertType::bStrToDFlt( m_osDEFAD,  &df1 ) )
    SetErrMsg( wxT("Invalid value for DEFAD.")  );

  if( ! ConvertType::bStrToDFlt( m_osDEFAS,  &df1 ) )
    SetErrMsg( wxT("Invalid value for DEFAS.")  );

  if( ! ConvertType::bStrToDFlt( m_osDEFL,   &df1 ) )
    SetErrMsg( wxT("Invalid value for DEFL.")   );

  if( ! ConvertType::bStrToDFlt( m_osDEFW,   &df1 ) )
    SetErrMsg( wxT("Invalid value for DEFW.")   );

  if( ! ConvertType::bStrToDFlt( m_osGMIN,   &df1 ) )
    SetErrMsg( wxT("Invalid value for GMIN.")   );

  if( ! ConvertType::bStrToDFlt( m_osPIVREL, &df1 ) )
    SetErrMsg( wxT("Invalid value for PIVREL.") );

  if( ! ConvertType::bStrToDFlt( m_osPIVTOL, &df1 ) )
    SetErrMsg( wxT("Invalid value for PIVTOL.") );

  if( ! ConvertType::bStrToDFlt( m_osRELTOL, &df1 ) )
    SetErrMsg( wxT("Invalid value for RELTOL.") );

  if( ! ConvertType::bStrToDFlt( m_osTEMP,   &df1 ) )
    SetErrMsg( wxT("Invalid value for TEMP.")   );

  if( ! ConvertType::bStrToDFlt( m_osTNOM,   &df1 ) )
    SetErrMsg( wxT("Invalid value for TNOM.")   );

  if( ! ConvertType::bStrToDFlt( m_osTRTOL,  &df1 ) )
    SetErrMsg( wxT("Invalid value for TRTOL.")  );

  if( ! ConvertType::bStrToDFlt( m_osVNTOL,  &df1 ) )
    SetErrMsg( wxT("Invalid value for VNTOL.")  );

  if( ! ConvertType::bStrToLong( m_osITL1,   &li1 ) )
    SetErrMsg( wxT("Invalid value for ITL1.") );

  if( ! ConvertType::bStrToLong( m_osITL2,   &li1 ) )
    SetErrMsg( wxT("Invalid value for ITL2.") );

  if( ! ConvertType::bStrToLong( m_osITL4,   &li1 ) )
    SetErrMsg( wxT("Invalid value for ITL4.") );

  if( m_osMETHOD.IsEmpty( ) )
    SetErrMsg( wxT("Invalid value for METHOD.") );

  return( bIsValid( ) );
}
