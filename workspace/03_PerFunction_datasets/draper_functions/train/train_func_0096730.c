doAutoScrollBars()
{
    int viewW = width()	 - frameWidth() - minViewX();
    int viewH = height() - frameWidth() - minViewY();
    bool vScrollOn = testTableFlags(Tbl_vScrollBar);
    bool hScrollOn = testTableFlags(Tbl_hScrollBar);
    int w = 0;
    int h = 0;
    int i;

    if ( testTableFlags(Tbl_autoHScrollBar) ) {
	if ( cellW ) {
	    w = cellW*nCols;
	} else {
	    i = 0;
	    while ( i < nCols && w <= viewW )
		w += cellWidth( i++ );
	}
	if ( w > viewW )
	    hScrollOn = true;
	else
	    hScrollOn = false;
    }

    if ( testTableFlags(Tbl_autoVScrollBar) ) {
	if ( cellH ) {
	    h = cellH*nRows;
	} else {
	    i = 0;
	    while ( i < nRows && h <= viewH )
		h += cellHeight( i++ );
	}

	if ( h > viewH )
	    vScrollOn = true;
	else
	    vScrollOn = false;
    }

    if ( testTableFlags(Tbl_autoHScrollBar) && vScrollOn && !hScrollOn )
	if ( w > viewW - VSBEXT )
	    hScrollOn = true;

    if ( testTableFlags(Tbl_autoVScrollBar) && hScrollOn && !vScrollOn )
	if ( h > viewH - HSBEXT )
	    vScrollOn = true;

    setHorScrollBar( hScrollOn, false );
    setVerScrollBar( vScrollOn, false );
    updateFrameSize();
}
