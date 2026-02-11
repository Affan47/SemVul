synchronizeStatus()
{
    DEBUG_BLOCK

    debug() << "new episodes status: " << m_uploadEpisodeStatusMap.size();

    if( Solid::Networking::status() == Solid::Networking::Unconnected )
        return;

    if( !m_uploadEpisodeStatusMap.isEmpty() )
    {
        m_episodeActionsResult =
                m_apiRequest->uploadEpisodeActions( m_username,
                                                    m_uploadEpisodeStatusMap.values() );


        connect( m_episodeActionsResult.data(), SIGNAL(finished()),
                 SLOT(slotSuccessfulStatusSynchronisation()) );
        connect( m_episodeActionsResult.data(),
                 SIGNAL(requestError(QNetworkReply::NetworkError)),
                 SLOT(synchronizeStatusRequestError(QNetworkReply::NetworkError)) );
        connect( m_episodeActionsResult.data(), SIGNAL(parseError()),
                 SLOT(synchronizeStatusParseError()) );

        Amarok::Components::logger()->shortMessage( i18n( "Trying to synchronize statuses with gpodder.net" ) );
    }
    else
        m_timerSynchronizeStatus->stop();
}
