DrawAMPM (Painter *painter) {
    if (canvas != nil) {
	if (AMPMmode != BLANK) {
	    if (AMPMmode == AM) {
		painter->FillPolygon(canvas, A.x, A.y, A.count);
	    } else {
		painter->FillPolygon(canvas, P.x, P.y, P.count);
	    }
	    painter->FillPolygon(canvas, M.x, M.y, M.count);
	}
    }
}
