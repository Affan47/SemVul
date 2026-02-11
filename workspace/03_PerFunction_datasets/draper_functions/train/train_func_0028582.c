AddEmptyLine( void )
{
  if( m_eReadMode == NVP_READ_ALL )
    m_FullFileData.push_back( pair<t_eDataType,string>(NVP_DATA_EMPTYLINE, "") );
}
