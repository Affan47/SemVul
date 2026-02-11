emitRedirections( const KUrl &oldUrl, const KUrl &newUrl )
{
    kDebug(7004) << oldUrl << "->" << newUrl;
    const QString oldUrlStr = oldUrl.url(KUrl::RemoveTrailingSlash);
    const QString newUrlStr = newUrl.url(KUrl::RemoveTrailingSlash);

    KIO::ListJob *job = jobForUrl( oldUrlStr );
    if ( job )
        killJob( job );


    DirectoryDataHash::iterator dit = directoryData.find(oldUrlStr);
    if ( dit == directoryData.end() )
        return;
    const QList<KDirLister *> listers = (*dit).listersCurrentlyListing;
    const QList<KDirLister *> holders = (*dit).listersCurrentlyHolding;

    KDirListerCacheDirectoryData& newDirData = directoryData[newUrlStr];


    foreach ( KDirLister *kdl, listers ) {
        if ( job )
            kdl->d->jobDone( job );

        emit kdl->canceled( oldUrl );
    }
    newDirData.listersCurrentlyListing += listers;


    foreach ( KDirLister *kdl, holders ) {
        if ( job )
            kdl->d->jobDone( job );
    }
    newDirData.listersCurrentlyHolding += holders;
    directoryData.erase(dit);

    if ( !listers.isEmpty() ) {
        updateDirectory( newUrl );


        foreach ( KDirLister *kdl, listers )
            emit kdl->started( newUrl );
    }


    foreach ( KDirLister *kdl, holders ) {
        kdl->d->redirect(oldUrl, newUrl, true );
    }
}
