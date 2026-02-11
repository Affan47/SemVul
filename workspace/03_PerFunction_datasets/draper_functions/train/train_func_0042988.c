updateItem( const Span& rowGeometry, const QPersistentModelIndex& idx )
{

    Updater updater( &m_isupdating );
    if ( !idx.isValid() || idx.data( ItemTypeRole )==TypeMulti ) {
        setRect( QRectF() );
	hide();
        return;
    }

    const Span s = scene()->grid()->mapToChart( idx );
    setPos( QPointF( s.start(), rowGeometry.start() ) );
    setRect( QRectF( 0., 0., s.length(), rowGeometry.length() ) );
    setIndex( idx );
    const Span bs = scene()->itemDelegate()->itemBoundingSpan( getStyleOption(), index() );

    setBoundingRect( QRectF( bs.start(), 0., bs.length(), rowGeometry.length() ) );
    const int maxh = scene()->rowController()->maximumItemHeight();
    if ( maxh < rowGeometry.length() ) {
        QRectF r = rect();
        const Qt::Alignment align = getStyleOption().displayAlignment;
        if ( align & Qt::AlignTop ) {

        } else if ( align & Qt::AlignBottom ) {
            r.setY( rowGeometry.length()-maxh );
        } else {

            r.setY( ( rowGeometry.length()-maxh ) / 2. );
        }
        r.setHeight( maxh );
        setRect( r );
    }


}
