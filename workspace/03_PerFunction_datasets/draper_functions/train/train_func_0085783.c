boxIntersectf(pointf pp, pointf cp, boxf * bp)
{
    pointf ipp;
    double ppx = pp.x;
    double ppy = pp.y;
    double cpx = cp.x;
    double cpy = cp.y;
    pointf ll;
    pointf ur;

    ll = bp->LL;
    ur = bp->UR;
    if (cp.x < ll.x) {
	ipp.x = ll.x;
	ipp.y = pp.y + (int) ((ipp.x - ppx) * (ppy - cpy) / (ppx - cpx));
	if (ipp.y >= ll.y && ipp.y <= ur.y)
	    return ipp;
    }
    if (cp.x > ur.x) {
	ipp.x = ur.x;
	ipp.y = pp.y + (int) ((ipp.x - ppx) * (ppy - cpy) / (ppx - cpx));
	if (ipp.y >= ll.y && ipp.y <= ur.y)
	    return ipp;
    }
    if (cp.y < ll.y) {
	ipp.y = ll.y;
	ipp.x = pp.x + (int) ((ipp.y - ppy) * (ppx - cpx) / (ppy - cpy));
	if (ipp.x >= ll.x && ipp.x <= ur.x)
	    return ipp;
    }
    if (cp.y > ur.y) {
	ipp.y = ur.y;
	ipp.x = pp.x + (int) ((ipp.y - ppy) * (ppx - cpx) / (ppy - cpy));
	if (ipp.x >= ll.x && ipp.x <= ur.x)
	    return ipp;
    }


    {
	char ppbuf[100], cpbuf[100], llbuf[100], urbuf[100];

	agerr(AGERR,
		"segment [%s,%s] does not intersect box ll=%s,ur=%s\n",
		pf2s(pp, ppbuf), pf2s(cp, cpbuf),
		pf2s(ll, llbuf), pf2s(ur, urbuf));
	assert(0);
    }
    return ipp;
}
