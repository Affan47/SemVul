redrawSegments(ocw, canvas, region)
OverTheSpotConversionWidget ocw;
Widget canvas;
XRectangle *region;
{
    DisplaySegment *dsp = ocw->overthespot.dispsegments;
    DisplayFragment *dfp;
    Widget dispobj = ocw->overthespot.displayobj;
    int i;

    for (i = 0; i < ocw->overthespot.numsegments; i++, dsp++) {
	for (dfp = dsp->fragments; dfp != NULL; dfp = dfp->next) {
	    if (dfp->canvas->canvas == canvas &&
		intersectRect(&dfp->region, region)) {
		CDDrawString(dispobj, canvas, &dsp->seg,
			      dfp->from, dfp->from + dfp->nchars,
			      dfp->region.x, dfp->region.y);
	    }
	}
    }
}
