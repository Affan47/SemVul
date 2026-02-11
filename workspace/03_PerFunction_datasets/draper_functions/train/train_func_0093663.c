draw( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &canvasRect ) const
{
    const QRectF cRect = QwtScaleMap::invTransform(
        xMap, yMap, canvasRect.toRect() );
    const QRectF bRect = boundingRect();
    if ( bRect.isValid() && cRect.isValid() )
    {
        QRectF rect = bRect;
        if ( bRect.contains( cRect ) )
            rect = cRect;

        const QRectF r = QwtScaleMap::transform( xMap, yMap, rect );
        render( painter, viewBox( rect ), r );
    }
}
