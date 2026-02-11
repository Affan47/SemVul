slotResultReady( const Meta::AlbumList &albums )
{
    DEBUG_BLOCK
    Collections::Collection *senderColl = m_queryMakers.value( qobject_cast<Collections::QueryMaker*>(sender()) );
    QSet<Meta::AlbumKey> albumSet;
    foreach( const Meta::AlbumPtr &albumPtr, albums )
    {
        albumSet.insert( Meta::AlbumKey( albumPtr ) );
    }
    if( senderColl == m_collectionA )
    {
        m_albumsA.unite( albumSet );
    }
    else if( senderColl == m_collectionB )
    {
        m_albumsB.unite( albumSet );
    }
    else
    {

    }
}
