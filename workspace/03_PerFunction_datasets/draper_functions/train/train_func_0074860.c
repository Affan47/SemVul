receiveQueryMakerDone()
{
    m_qm->deleteLater();
    m_qm = 0;

    if (( m_domain.size() > 0 ) || m_domainReductionFailed ) {
        if ( m_domain.size() <= 0 ) {
            Amarok::Components::logger()->shortMessage( i18n("The playlist generator failed to load any tracks from the collection.") );
        }
        m_readyToRun = true;
        emit readyToRun();
    } else {
        Amarok::Components::logger()->longMessage(
                    i18n("There are no tracks that match all constraints. " \
                         "The playlist generator will find the tracks that match best, " \
                "but you may want to consider loosening the constraints to find more tracks.") );
        m_domainReductionFailed = true;


        m_qm = new Collections::MetaQueryMaker( CollectionManager::instance()->queryableCollections() );
        if ( m_qm ) {
            connect( m_qm, SIGNAL(newResultReady(Meta::TrackList)), this, SLOT(receiveQueryMakerData(Meta::TrackList)), Qt::QueuedConnection );
            connect( m_qm, SIGNAL(queryDone()), this, SLOT(receiveQueryMakerDone()), Qt::QueuedConnection );

            m_qm->setQueryType( Collections::QueryMaker::Track );
            m_qm->run();
        }
    }
}
