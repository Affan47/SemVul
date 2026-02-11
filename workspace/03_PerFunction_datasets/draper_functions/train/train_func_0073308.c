getScrollMode( const QPoint &p,
    QwtAbstractSlider::ScrollMode &scrollMode, int &direction ) const
{
    if ( !d_data->sliderRect.contains( p ) )
    {
        scrollMode = QwtAbstractSlider::ScrNone;
        direction = 0;
        return;
    }

    const int pos = ( orientation() == Qt::Horizontal ) ? p.x() : p.y();
    const int markerPos = transform( value() );

    if ( ( pos > markerPos - d_data->handleSize.width() / 2 )
        && ( pos < markerPos + d_data->handleSize.width() / 2 ) )
    {
        scrollMode = QwtAbstractSlider::ScrMouse;
        direction = 0;
        return;
    }

    scrollMode = QwtAbstractSlider::ScrPage;
    direction = ( pos > markerPos ) ? 1 : -1;

    if ( scaleDraw()->scaleMap().p1() > scaleDraw()->scaleMap().p2() )
        direction = -direction;
}
