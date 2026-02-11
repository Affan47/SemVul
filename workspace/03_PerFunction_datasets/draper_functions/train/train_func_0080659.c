adjustregularpath(path * P, int fb, int lb)
{
    boxf *bp1, *bp2;
    int i, x;

    for (i = fb-1; i < lb+1; i++) {
	bp1 = &P->boxes[i];
	if ((i - fb) % 2 == 0) {
	    if (bp1->LL.x >= bp1->UR.x) {
		x = (bp1->LL.x + bp1->UR.x) / 2;
		bp1->LL.x = x - HALFMINW, bp1->UR.x = x + HALFMINW;
	    }
	} else {
	    if (bp1->LL.x + MINW > bp1->UR.x) {
		x = (bp1->LL.x + bp1->UR.x) / 2;
		bp1->LL.x = x - HALFMINW, bp1->UR.x = x + HALFMINW;
	    }
	}
    }
    for (i = 0; i < P->nbox - 1; i++) {
	bp1 = &P->boxes[i], bp2 = &P->boxes[i + 1];
	if (i >= fb && i <= lb && (i - fb) % 2 == 0) {
	    if (bp1->LL.x + MINW > bp2->UR.x)
		bp2->UR.x = bp1->LL.x + MINW;
	    if (bp1->UR.x - MINW < bp2->LL.x)
		bp2->LL.x = bp1->UR.x - MINW;
	} else if (i + 1 >= fb && i < lb && (i + 1 - fb) % 2 == 0) {
	    if (bp1->LL.x + MINW > bp2->UR.x)
		bp1->LL.x = bp2->UR.x - MINW;
	    if (bp1->UR.x - MINW < bp2->LL.x)
		bp1->UR.x = bp2->LL.x + MINW;
	}
    }
}
