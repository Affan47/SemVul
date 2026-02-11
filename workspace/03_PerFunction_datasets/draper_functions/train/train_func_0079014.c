slotTrackChanged( Meta::TrackPtr track )
{
    m_trackToSyncStatus = NULL;

    if( track != Meta::TrackPtr( 0 ) )
    {

        if( ( this->possiblyContainsTrack( track->uidUrl() ) ) ||
                ( this->possiblyContainsTrack( track->uidUrl() ) &&
                  The::playlistManager()->defaultPodcasts()->possiblyContainsTrack( track->uidUrl() )
                  ) )
        {
            m_trackToSyncStatus = track;

            QTimer::singleShot( 10000, this, SLOT(timerPrepareToSyncPodcastStatus()) );


            createPlayStatusBookmark();

            return;
        }
    }

    m_timerGeneratePlayAction->stop();


    m_timerSynchronizeStatus->start( 60000 );
}
