calculateGradientStops( const Gradient& gradient )
{
    QPolygonF red = interpolateCubic( gradient.red() );
    QPolygonF green = interpolateCubic( gradient.green() );
    QPolygonF blue = interpolateCubic( gradient.blue() );

    QGradientStops stops;

    if ( red.isEmpty() || green.isEmpty() || blue.isEmpty() )
        return stops;

    stops.append( makeStop( 0.0, red.first().y(), green.first().y(), blue.first().y() ) );

    double x = 0.0;
    int ri = 1, gi = 1, bi = 1;
    while ( ri < red.count() && gi < green.count() && bi < blue.count() ) {
        double rx = red.at( ri ).x();
        double gx = green.at( gi ).x();
        double bx = blue.at( bi ).x();
        x = qMin( qMin( rx, gx ), bx );
        stops.append( makeStop( x, lerp( red, ri, x ), lerp( green, gi, x ), lerp( blue, bi, x ) ) );
        if ( rx == x )
            ri++;
        if ( gx == x )
            gi++;
        if ( bx == x )
            bi++;
    }

    return stops;
}
