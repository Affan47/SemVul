recordointrsx(XLabels_t * xlp, object_t * op, object_t * cp, Rect_t * rp,
	      double a, object_t * intrsx[XLNBR])
{
    int i = getintrsxi(xlp, op, cp);
    if (i < 0)
	i = 5;
    if (intrsx[i] != NULL) {
	double sa, maxa = 0.0;
	Rect_t srect;

	objp2rect(intrsx[i], &srect);
	sa = aabbaabb(rp, &srect);
	if (sa > a)
	    maxa = sa;

	if (intrsx[i]->lbl) {
	    objplp2rect(intrsx[i], &srect);
	    sa = aabbaabb(rp, &srect);
	    if (sa > a)
		maxa = sa > maxa ? sa : maxa;
	}
	if (maxa > 0.0)
	    return maxa;

	intrsx[i] = cp;
	return a;
    }
    intrsx[i] = cp;
    return a;
}
