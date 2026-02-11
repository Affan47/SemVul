backupFile( const QString& qFilename, const QString& backupDir )
{


    KConfigGroup g(KGlobal::config(), "Backups");
    QString type = g.readEntry( "Type", "simple" );
    QString extension = g.readEntry( "Extension", "~" );
    QString message = g.readEntry( "Message", "Automated KDE Commit" );
    int maxnum = g.readEntry( "MaxBackups", 10 );
    if ( type.toLower() == QLatin1String("numbered") ) {
        return( numberedBackupFile( qFilename, backupDir, extension, maxnum ) );
    } else if ( type.toLower() == QLatin1String("rcs") ) {
        return( rcsBackupFile( qFilename, backupDir, message ) );
    } else {
        return( simpleBackupFile( qFilename, backupDir, extension ) );
    }
}
