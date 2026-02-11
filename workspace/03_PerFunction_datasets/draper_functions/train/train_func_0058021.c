paintEvent( QPaintEvent* ) {
    QPainter p;
    p.begin( this );

    p.drawPixmap( 0, 0, *Image );

    p.setPen( QPen( QColor( "Grey" ), 2 ) );
    p.drawRect( *CropRect );

    p.setPen( QPen( QColor( "Grey" ), 0 ) );
    p.drawRect( QRect( CropRect->left(), CropRect->top(),
                       HandleSize, HandleSize ) );
    p.drawRect( QRect( CropRect->right() - HandleSize, CropRect->top(),
                       HandleSize, HandleSize ) );
    p.drawRect( QRect( CropRect->left(), CropRect->bottom() - HandleSize,
                       HandleSize, HandleSize ) );
    p.drawRect( QRect( CropRect->right() - HandleSize, CropRect->bottom() - HandleSize,
                       HandleSize, HandleSize ) );

    if ( CropRect->x() > 0 )
        p.fillRect( 0, 0, CropRect->x(), height(),
                    QBrush( QColor("white"), Qt::Dense3Pattern ) );
    if ( CropRect->right() < width() )
        p.fillRect( CropRect->right(), 0, (width() - CropRect->right()), height(),
                    QBrush( QColor("white"), Qt::Dense3Pattern ) );
    if ( CropRect->y() > 0 )
        p.fillRect( 0, 0, width(), CropRect->y(),
                    QBrush( QColor("white"), Qt::Dense3Pattern ) );
    if ( CropRect->bottom() < height() )
        p.fillRect( 0, CropRect->bottom(), width(), (height() - CropRect->bottom()),
                    QBrush( QColor("white"), Qt::Dense3Pattern ) );

    p.end();
}
