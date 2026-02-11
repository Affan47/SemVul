slotDeviceDetected(MediaDeviceInfo* info)
{
    MediaDeviceCollection* coll = 0;

    if( !m_collectionMap.contains( info->udi() ) )
    {

        coll = createCollection( info );


        if( coll )
        {

            m_collectionMap.insert( info->udi(), coll );
            connect( coll, SIGNAL(collectionReady(Collections::Collection*)),
                     this, SIGNAL(newCollection(Collections::Collection*)) );
            connect( coll, SIGNAL(collectionDisconnected(QString)),
                     this, SLOT(slotDeviceDisconnected(QString)) );
            coll->init();
        }
    }
}
