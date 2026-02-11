operator&( const QRect &r ) const
{
    QRect tmp;
    tmp.x1 = QMAX( x1, r.x1 );
    tmp.x2 = QMIN( x2, r.x2 );
    tmp.y1 = QMAX( y1, r.y1 );
    tmp.y2 = QMIN( y2, r.y2 );
    return tmp;
}
