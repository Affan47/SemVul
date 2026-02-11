adjustMaps( QwtScaleMap &xMap, QwtScaleMap &yMap,
    const QRectF &area, const QRectF &paintRect)
{
    double sx1 = area.left();
    double sx2 = area.right();
    if ( xMap.isInverting() )
        qSwap(sx1, sx2);

    double sy1 = area.top();
    double sy2 = area.bottom();

    if ( yMap.isInverting() )
        qSwap(sy1, sy2);

    xMap.setPaintInterval(paintRect.left(), paintRect.right());
    xMap.setScaleInterval(sx1, sx2);

    yMap.setPaintInterval(paintRect.top(), paintRect.bottom());
    yMap.setScaleInterval(sy1, sy2);
}
