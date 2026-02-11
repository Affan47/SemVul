computeDisplayFragments(ocw, newseg, disploc)
OverTheSpotConversionWidget ocw;
ICString *newseg;
DisplayLocation *disploc;
{
    int start;
    int nchars;
    Widget dispobj = ocw->overthespot.displayobj;
    DisplayFragment *fragments, *dfp;
    int widthavailable;

    TRACE(("computeDisplayFragments()\n"));
    start = 0;
    fragments = NULL;
    while (start < newseg->nchars) {
	widthavailable = computeWidthAvailable(ocw, disploc);
	nchars = CDMaxChar(dispobj, newseg, start, widthavailable);
	if (nchars == 0) {
	    if (disploc->canvas->x <= CLAREA(ocw).x &&
		disploc->x == 0) {


		nchars = 1;
	    }
	}
	TRACE(("\twidthavailable=%d, start=%d, maxchar=%d\n", widthavailable, start, nchars));
	if (nchars > 0) {
	    if (fragments == NULL) {
		fragments = dfp = allocDisplayFragment();
	    } else {
		dfp->next = allocDisplayFragment();
		dfp = dfp->next;
	    }
	    dfp->from = start;
	    dfp->nchars = nchars;
	    dfp->canvas = disploc->canvas;
	    dfp->region.x = disploc->x;
	    dfp->region.y = disploc->y;
	    dfp->region.width = CDStringWidth(dispobj, newseg, start,
						    start + nchars);
	    dfp->region.height = ocw->overthespot.lineheight;
	    dfp->next = NULL;

	    disploc->x += dfp->region.width;
	}
	start += nchars;
	if (start < newseg->nchars) nextLocation(ocw, disploc);
    }

    return fragments;
}
