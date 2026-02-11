handleArtists( const QStringList &result )
{
    Meta::ArtistList artists;

    int rowCount = m_metaFactory->getArtistSqlRowCount();
    int resultRows = result.size() / rowCount;
    for( int i = 0; i < resultRows; i++ )
    {
        QStringList row = result.mid( i*rowCount, rowCount );
        artists.append( m_registry->getArtist( row ) );
    }
    emit newResultReady( artists );
}
