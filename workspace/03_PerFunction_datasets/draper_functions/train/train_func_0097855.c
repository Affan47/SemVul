episodeActionsInCascadeRequestError( QNetworkReply::NetworkError error )
{
    DEBUG_BLOCK

    QTimer::singleShot( 10000, this, SLOT(requestEpisodeActionsInCascade()) );


    m_channelsToRequestActions.enqueue( m_channelsToRequestActions.dequeue() );

    debug() << "episodeActionsInCascade [Status Synchronization] - Request error nr.: " << error;
}
