handleAlbumResult()
{
    DEBUG_BLOCK
    QSet<Meta::AlbumKey> albumsOnlyInA = m_albumsA - m_albumsB;
    QSet<Meta::AlbumKey> albumsOnlyInB = m_albumsB - m_albumsA;
    QSet<Meta::AlbumKey> albumsInBoth = m_albumsA & m_albumsB;

    foreach( const Meta::AlbumKey &album, albumsOnlyInA )
    {
        m_albumResult.insert( album, OnlyInA );
    }
    foreach( const Meta::AlbumKey &album, albumsOnlyInB )
    {
        m_albumResult.insert( album, OnlyInB );
    }
    foreach( const Meta::AlbumKey &album, albumsInBoth )
    {
        m_albumResult.insert( album, InBoth );
    }
    Collections::QueryMaker *qmA = setupTrackQuery( m_collectionA );
    Collections::QueryMaker *qmB = setupTrackQuery( m_collectionB );
    qmA->beginAnd();
    qmB->beginAnd();
    {
        QHashIterator<QString, InSet> iter( m_artistResult );
        while( iter.hasNext() )
        {
            iter.next();
            QString artist = iter.key();
            InSet currentStatus = iter.value();
            if( currentStatus == OnlyInA )
            {
                qmA->excludeFilter( Meta::valArtist, artist, true, true );
            }
            if( currentStatus == OnlyInB )
            {
                qmB->excludeFilter( Meta::valArtist, artist, true, true );
            }
        }
    }
    {
        QHashIterator<Meta::AlbumKey, InSet> iter( m_albumResult );
        while( iter.hasNext() )
        {
            iter.next();
            Meta::AlbumKey album = iter.key();
            InSet currentStatus = iter.value();
            if( currentStatus == OnlyInA )
            {
                qmA->beginOr();
                qmA->excludeFilter( Meta::valAlbum, album.albumName(), true, true );
                qmA->excludeFilter( Meta::valAlbumArtist, album.artistName(), true, true );
                qmA->endAndOr();
            }
            if( currentStatus == OnlyInB )
            {
                qmB->beginOr();
                qmB->excludeFilter( Meta::valAlbum, album.albumName(), true, true );
                qmB->excludeFilter( Meta::valAlbumArtist, album.artistName(), true, true );
                qmB->endAndOr();
            }
        }
    }
    qmA->endAndOr();
    qmB->endAndOr();
    m_timer.start();
    qmA->run();
    qmB->run();
}
