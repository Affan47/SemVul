exists( const KUrl & url, bool source, QWidget* window )
{
  if ( url.isLocalFile() )
    return QFile::exists( url.toLocalFile() );
  NetAccess kioNet;
  return kioNet.statInternal( url, 0 ,
                              source ? SourceSide : DestinationSide, window );
}
