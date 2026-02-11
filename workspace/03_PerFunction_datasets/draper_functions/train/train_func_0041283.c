paintEvent( QPaintEvent *e ) {

    QFrame::paintEvent( e );
    QPainter p;

    p.begin( this );
    p.setRenderHint( QPainter::Antialiasing, d->useAntialias );
    p.fillRect( rect(), backgroundColor() );
    p.translate( leftPadding() + 0.5, topPadding() + 0.5 );

    setPixRect();
    p.setClipRect( d->pixRect );
    p.setClipping( true );

    resetPlotMask();

    foreach( KPlotObject *po, d->objectList )
        po->draw( &p, this );


    p.setClipping( false );
    drawAxes( &p );

    p.end();
}
