GetDfltLogLevelForDevice( const string& sLogDevice )
{
  if( sLogDevice == STR_LOGDEV_CONSOLE )
    return CFG_DFLT_LOGLEVEL_CONSOLE;

  if( sLogDevice == STR_LOGDEV_STDERR )
    return CFG_DFLT_LOGLEVEL_STDERR;

  if( sLogDevice == STR_LOGDEV_FILE )
    return CFG_DFLT_LOGLEVEL_FILE;

  if( sLogDevice == STR_LOGDEV_SYSLOG )
    return CFG_DFLT_LOGLEVEL_SYSLOG;


  return CFG_DFLT_LOGLEVEL;
}
