calculateNearbyPoint( const QRect &target) {
    QPoint pos = target.topLeft();
    int x = pos.x();
    int y = pos.y();
    int w = minimumSizeHint().width();
    int h = minimumSizeHint().height();

    QRect r = KGlobalSettings::desktopGeometry(QPoint(x+w/2,y+h/2));

    if( d->popupStyle == Balloon )
    {

        if( x + w > r.width() ){
            x = x + target.width();
        }

        if( y + h > r.height() ){
            y = y + target.height();
        }
    } else
    {
        if ( x < r.center().x() )
            x = x + target.width();
        else
            x = x - w;


        if ( (y + h) > r.bottom() )
            y = r.bottom() - h;

        if ( (x + w) > r.right() )
            x = r.right() - w;
    }
    if ( y < r.top() )
        y = r.top();

    if ( x < r.left() )
        x = r.left();

    return QPoint( x, y );
}
