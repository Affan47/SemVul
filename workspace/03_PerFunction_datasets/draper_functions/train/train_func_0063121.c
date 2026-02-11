Initialize( const string& aConfigFile, const t_accessMode aEAccessMode, const string& aDfltCfgFile )
{

  m_sDfltCfgFile = aDfltCfgFile;


  m_pConfig = new NameValueConfig( aConfigFile, aEAccessMode );
}
