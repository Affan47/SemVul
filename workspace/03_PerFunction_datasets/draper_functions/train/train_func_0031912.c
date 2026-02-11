boundingRect() const
{
    const QwtInterval intervalX = interval( Qt::XAxis );
    const QwtInterval intervalY = interval( Qt::YAxis );

    if ( !intervalX.isValid() && !intervalY.isValid() )
        return QRectF();

    QRectF r;

    if ( intervalX.isValid() )
    {
        r.setLeft( intervalX.minValue() );
        r.setRight( intervalX.maxValue() );
    }
    else
    {
        r.setLeft(-0.5 * FLT_MAX);
        r.setWidth(FLT_MAX);
    }

    if ( intervalY.isValid() )
    {
        r.setTop( intervalY.minValue() );
        r.setBottom( intervalY.maxValue() );
    }
    else
    {
        r.setTop(-0.5 * FLT_MAX);
        r.setHeight(FLT_MAX);
    }

    return r.normalized();
}
