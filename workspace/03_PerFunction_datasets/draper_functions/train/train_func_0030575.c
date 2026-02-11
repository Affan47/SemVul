drawBackground( QPainter * painter, const QRectF & rect )
{
    QRectF source = rect.translated( -sceneRect().topLeft() );
    if ( m_background.size() != size() )
    {
        qreal xScale = m_background.width() / width();
        qreal yScale = m_background.height() / height();
        source = QRectF( source.x() * xScale,
                         source.y() * yScale,
                         source.width() * xScale,
                         source.height() * yScale );
    }

    painter->drawPixmap( rect, m_background, source );
}
