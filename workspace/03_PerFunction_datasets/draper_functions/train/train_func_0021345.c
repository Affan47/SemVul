simpleBackupFile( const QString& qFilename,
                                  const QString& backupDir,
                                  const QString& backupExtension )
{
    QString backupFileName = qFilename + backupExtension;

    if ( !backupDir.isEmpty() ) {
        QFileInfo fileInfo ( qFilename );
        backupFileName = backupDir + QLatin1Char('/') + fileInfo.fileName() + backupExtension;
    }


    QFile::remove(backupFileName);
    return QFile::copy(qFilename, backupFileName);
}
