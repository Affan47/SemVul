pixelDist( int axis, const QSize &size ) const
{
    const QwtInterval intv = intervalHint( axis );

    double dist = 0.0;
    if ( !intv.isNull() )
    {
        if ( axis == referenceAxis() )
            dist = intv.width();
        else
        {
            const double r = aspectRatio( axis );
            if ( r > 0.0 )
                dist = intv.width() * r;
        }
    }

    if ( dist > 0.0 )
    {
        if ( orientation( axis ) == Qt::Horizontal )
            dist /= size.width();
        else
            dist /= size.height();
    }

    return dist;
}
