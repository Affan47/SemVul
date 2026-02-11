updateDisplay(ocw)
OffTheSpotConversionWidget ocw;
{
    DisplaySegment *dsp = ocw->offthespot.dispsegments;
    int i;

    for (i = 0; i < ocw->offthespot.numsegments; i++, dsp++) {
	if (dsp->redrawpos >= 0) {
	    TRACE(("updateDisplaySegment(seg#=%d)\n", i));
	    updateDisplaySegment(ocw, dsp);
	}
    }
}
