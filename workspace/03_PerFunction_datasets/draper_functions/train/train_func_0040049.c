overlaps(nitem * p, int cnt)
{
    int i, j;
    nitem *pi = p;
    nitem *pj;

    for (i = 0; i < cnt - 1; i++) {
	pj = pi + 1;
	for (j = i + 1; j < cnt; j++) {
	    if (overlap(pi->bb, pj->bb))
		return 1;
	    pj++;
	}
	pi++;
    }
    return 0;
}
