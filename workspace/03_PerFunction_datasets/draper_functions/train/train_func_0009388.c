slotFileDeleted( const QString& path )
{
    kDebug(7004) << path;
    KUrl u( path );
    QStringList fileUrls;
    Q_FOREACH(KUrl url, directoriesForCanonicalPath(u.directory())) {
        url.addPath(u.fileName());
        fileUrls << url.url();
    }
    slotFilesRemoved(fileUrls);
}
