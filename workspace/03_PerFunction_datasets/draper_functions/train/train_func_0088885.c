playAudioCd()
{
    DEBUG_BLOCK


    QList<Collections::Collection*> collections = CollectionManager::instance()->viewableCollections();


    foreach( Collections::Collection *collection, collections )
    {
        if( collection->collectionId() == "AudioCd" )
        {

            debug() << "got audiocd collection";

            Collections::MemoryCollection * cdColl = dynamic_cast<Collections::MemoryCollection *>( collection );

            if( !cdColl || cdColl->trackMap().count() == 0 )
            {
                debug() << "cd collection not ready yet (track count = 0 )";
                m_waitingForCd = true;
                return false;
            }

            The::playlistController()->insertOptioned( cdColl->trackMap().values(), Playlist::OnPlayMediaAction );
            m_waitingForCd = false;
            return true;
        }
    }

    debug() << "waiting for cd...";
    m_waitingForCd = true;
    return false;
}
