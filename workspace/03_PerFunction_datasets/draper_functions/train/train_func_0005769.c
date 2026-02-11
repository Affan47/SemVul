moveArrow( const QPoint &pos )
{
    int val;
    int w = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    int iw = (w < ARROWSIZE) ? ARROWSIZE : w;

    if ( orientation() == Qt::Vertical )
        val = ( maximum() - minimum() ) * (height() - pos.y() - iw)
            / (height() - iw * 2) + minimum();
    else
        val = ( maximum() - minimum() ) * ( pos.x() - iw)
            / (width() - iw * 2) + minimum();

    setValue( val );
    update();
}
