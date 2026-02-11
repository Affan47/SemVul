symlink(const QString &target, const KUrl &dest,
                                  JobFlags flags)
{
    kDebug() << target << ", " << dest;

    KUrl new_dest;
    if ( d->internalRewriteUrl(dest, new_dest) )
    {
        KIO::SimpleJob *job = KIO::symlink(target, new_dest, flags & HideProgressInfo);
        d->connectSimpleJob(job);

        d->eventLoop.exec();
    }
    else
    {
        error( KIO::ERR_MALFORMED_URL, dest.prettyUrl() );
    }
}
