startRemoveJobs()
{
    DEBUG_BLOCK
    while ( !m_removetracks.isEmpty() )
    {
        Meta::TrackPtr track = m_removetracks.takeFirst();
        KUrl src = track->playableUrl();

        KIO::DeleteJob *job = 0;

        src.cleanPath();
        debug() << "deleting  " << src;
        KIO::JobFlags flags = KIO::HideProgressInfo;
        job = KIO::del( src, flags );
        connect( job, SIGNAL(result(KJob*)), SLOT(slotRemoveJobFinished(KJob*)) );
        QString name = track->prettyName();
        if( track->artist() )
            name = QString( "%1 - %2" ).arg( track->artist()->name(), track->prettyName() );

        Amarok::Components::logger()->newProgressOperation( job, i18n( "Removing: %1", name ) );
        m_removejobs.insert( job, track );
    }
}
