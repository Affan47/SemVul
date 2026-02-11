setHorScrollBar( bool on, bool update )
{
    if ( on ) {
	tFlags |= Tbl_hScrollBar;
	horizontalScrollBar();
	if ( update )
	    updateScrollBars( horMask | verMask );
	else
	    sbDirty = sbDirty | (horMask | verMask);
	if ( testTableFlags( Tbl_vScrollBar ) )
	    coverCornerSquare( true );
	if ( autoUpdate() )
	    sbDirty = sbDirty | horMask;
    } else {
	tFlags &= ~Tbl_hScrollBar;
	if ( !hScrollBar )
	    return;
	coverCornerSquare( false );
	bool hideScrollBar = autoUpdate() && hScrollBar->isVisible();
	if ( hideScrollBar )
	    hScrollBar->hide();
	if ( update )
	    updateScrollBars( verMask );
	else
	    sbDirty = sbDirty | verMask;
	if ( hideScrollBar && isVisible() )
	    repaint( hScrollBar->x(), hScrollBar->y(),
		     width() - hScrollBar->x(), hScrollBar->height() );
    }
    if ( update )
	updateFrameSize();
}
