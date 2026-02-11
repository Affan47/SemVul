updateDisplaySegment(dispobj, dsp)
Widget dispobj;
DisplaySegment *dsp;
{
    DisplayFragment *dfp = dsp->fragments;
    int from;
    int x;

    while (dfp != NULL) {
	if (dsp->redrawpos < dfp->from + dfp->nchars) {
	    from = (dsp->redrawpos > dfp->from) ? dsp->redrawpos : dfp->from;
	    x = dfp->region.x;
	    if (from > dfp->from) {
		x += CDStringWidth(dispobj, &dsp->seg, dfp->from, from);
	    }
	    CDDrawString(dispobj, dfp->canvas->canvas, &dsp->seg,
			 from, dfp->from + dfp->nchars,
			 x, dfp->region.y);
	}
	dfp = dfp->next;
    }
}
