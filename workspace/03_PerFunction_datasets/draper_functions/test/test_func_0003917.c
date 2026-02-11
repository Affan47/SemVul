invTransform( const QPoint &pos ) const
{
    QwtScaleMap xMap = plot()->canvasMap( d_xAxis );
    QwtScaleMap yMap = plot()->canvasMap( d_yAxis );

    return QPointF(
        xMap.invTransform( pos.x() ),
        yMap.invTransform( pos.y() )
    );
}
