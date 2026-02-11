submitRendering( const QString & elementId, const QImage & image )
{
    QPixmap pix;


    if ( image.size() != currentCardSize )
        return;


    if ( !cache->findPixmap( keyForPixmap( elementId, currentCardSize ), &pix ) )
        pix = QPixmap::fromImage( image );

    QHash<QString,CardElementData>::iterator it;
    it = frontIndex.find( elementId );
    if ( it != frontIndex.end() )
    {
        it.value().cardPixmap = pix;
        foreach ( KCard * c, it.value().cardUsers )
            c->setFrontPixmap( pix );
    }

    it = backIndex.find( elementId );
    if ( it != backIndex.end() )
    {
        it.value().cardPixmap = pix;
        foreach ( KCard * c, it.value().cardUsers )
            c->setBackPixmap( pix );
    }
}
