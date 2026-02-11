userDefinedServices( const QString& path, bool bLocalFiles )
{
    KDesktopFile cfg( path );
    return userDefinedServices( path, cfg, bLocalFiles );
}
