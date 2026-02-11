Validate_DnsServer( const string& sDnsServer )
{

  if( sDnsServer.size() == 0 ) return true;


  if( sDnsServer.size() > CFG_MAX_DNSSERVER )
  {
    gssLastError = GOGOC_UIS__G6V_DNSSERVERSTOOLONG;
    return false;
  }


  char* szDNSServers;
  char* szServer;
  string sServer;

  szDNSServers = pal_strdup( sDnsServer.c_str() );
  for(szServer = strtok(szDNSServers, ":");szServer; szServer=strtok(NULL, ":") )
  {
    sServer = szServer;


    if( sServer.find_first_not_of( CFG_DNS_CHRS ) != string::npos )
    {
      gssLastError = GOGOC_UIS__G6V_DNSSERVERSINVALIDCHRS;
      free( szDNSServers );
      return false;
    }


  }
  free( szDNSServers );

  return true;
}
