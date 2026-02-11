updateSqlChannel( Podcasts::SqlPodcastChannelPtr channel )
{
    if( channel.isNull() )
        return;
    if( m_updatingChannels >= m_maxConcurrentUpdates )
    {
        debug() << QString( "Maximum concurrent updates (%1) reached. "
                            "Queueing \"%2\" for download." )
                .arg( m_maxConcurrentUpdates )
                .arg( channel->title() );
        m_updateQueue << channel;
        return;
    }

    PodcastReader *podcastReader = new PodcastReader( this );

    connect( podcastReader, SIGNAL(finished(PodcastReader*)),
             SLOT(slotReadResult(PodcastReader*)) );
    connect( podcastReader, SIGNAL(statusBarSorryMessage(QString)),
            this, SLOT(slotStatusBarSorryMessage(QString)) );
    connect( podcastReader, SIGNAL(statusBarNewProgressOperation(KIO::TransferJob*,QString,Podcasts::PodcastReader*)),
                this, SLOT(slotStatusBarNewProgressOperation(KIO::TransferJob*,QString,Podcasts::PodcastReader*)) );

    m_updatingChannels++;
    podcastReader->update( Podcasts::PodcastChannelPtr::dynamicCast( channel ) );
}
