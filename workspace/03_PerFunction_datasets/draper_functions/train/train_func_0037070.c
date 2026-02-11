run()
{
    foreach( const KCardTheme & theme, m_themes )
    {
        {
            QMutexLocker l( &m_haltMutex );
            if ( m_haltFlag )
                return;
        }

        QImage img( d->previewSize, QImage::Format_ARGB32 );
        img.fill( Qt::transparent );
        QPainter p( &img );

        QSvgRenderer renderer( theme.graphicsFilePath() );

        QSizeF size = renderer.boundsOnElement("back").size();
        size.scale( 1.5 * d->baseCardSize.width(), d->baseCardSize.height(), Qt::KeepAspectRatio );

        qreal yPos = ( d->previewSize.height() - size.height() ) / 2;
        qreal spacingWidth = d->baseCardSize.width()
                             * ( d->previewSize.width() - d->previewLayout.size() * size.width() )
                             / ( d->previewSize.width() - d->previewLayout.size() * d->baseCardSize.width() );

        qreal xPos = 0;
        foreach ( const QList<QString> & pile, d->previewLayout )
        {
            foreach ( const QString & card, pile )
            {
                renderer.render( &p, card, QRectF( QPointF( xPos, yPos ), size ) );
                xPos += 0.3 * spacingWidth;
            }
            xPos += 1 * size.width() + ( 0.1 - 0.3 ) * spacingWidth;
        }

        emit previewRendered( theme, img );
    }
}
