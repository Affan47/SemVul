image( int size ) const
{
    if( size > 1000 )
    {
        debug() << "Giant image detected, are you sure you want this?";
        return Meta::Album::image( size );
    }

    const QString artist = hasAlbumArtist() ?
        albumArtist()->name() :
        QLatin1String("NULL");

    const QString coverName = QString( "%1_%2_%3_cover.png" ).arg( downloadPrefix(), artist, name() );
    const QString saveLocation = Amarok::saveLocation( "albumcovers/cache/" );
    const QDir cacheCoverDir = QDir( saveLocation );


    if( !cacheCoverDir.exists() )
        cacheCoverDir.mkpath( saveLocation );

    if( size <= 1 )
        size = 100;

    const QString sizeKey = QString::number( size ) + QLatin1Char('@');
    const QString cacheCoverPath = cacheCoverDir.filePath( sizeKey + coverName );

    if( QFile::exists( cacheCoverPath ) )
    {
        return QImage( cacheCoverPath );
    }
    else if( m_hasFetchedCover && !m_cover.isNull() )
    {
        QImage image( m_cover.scaled( size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
        image.save( cacheCoverPath, "PNG" );
        return image;
    }
    else if( !m_isFetchingCover && !coverUrl().isEmpty() )
    {
        m_isFetchingCover = true;

        ( new ServiceAlbumCoverDownloader )->downloadCover(
            ServiceAlbumWithCoverPtr(const_cast<ServiceAlbumWithCover*>(this)) );
    }

    return Meta::Album::image( size );
}
