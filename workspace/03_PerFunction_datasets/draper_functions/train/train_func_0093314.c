drawTick( QPainter *painter, double value, double len ) const
{
    if ( len <= 0 )
        return;

    const double tval = scaleMap().transform( value );

    const double cx = d_data->center.x();
    const double cy = d_data->center.y();
    const double radius = d_data->radius;

    if ( ( tval <= d_data->startAngle + 359 * 16 )
        || ( tval >= d_data->startAngle - 359 * 16 ) )
    {
        const double arc = double( tval ) / 16.0 * M_PI / 180.0;

        const double sinArc = qSin( arc );
        const double cosArc = qCos( arc );

        const double x1 = cx + radius * sinArc;
        const double x2 = cx + ( radius + len ) * sinArc;
        const double y1 = cy - radius * cosArc;
        const double y2 = cy - ( radius + len ) * cosArc;

        QwtPainter::drawLine( painter, x1, y1, x2, y2 );
    }
}
