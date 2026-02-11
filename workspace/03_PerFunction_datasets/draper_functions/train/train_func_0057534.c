ftpOpenDir( const QString & path )
{


  QString tmp = path.isEmpty() ? QString("/") : path;


  if( !ftpFolder(tmp, false) )
      return false;


  if( !ftpOpenCommand( "list -la", QString(), 'I', ERR_CANNOT_ENTER_DIRECTORY ) )
  {
    if ( !ftpOpenCommand( "list", QString(), 'I', ERR_CANNOT_ENTER_DIRECTORY ) )
    {
      kWarning(7102) << "Can't open for listing";
      return false;
    }
  }
  kDebug(7102) << "Starting of list was ok";
  return true;
}
