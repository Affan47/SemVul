removeDirFromCache( const KUrl& dir )
{
    kDebug(7004) << dir;
    const QList<QString> cachedDirs = itemsCached.keys();
    foreach(const QString& cachedDir, cachedDirs) {
        if ( dir.isParentOf( KUrl( cachedDir ) ) )
            itemsCached.remove( cachedDir );
    }
}
