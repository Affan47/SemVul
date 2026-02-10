completeregularpath(path * P, edge_t * first, edge_t * last,
		    pathend_t * tendp, pathend_t * hendp, boxf * boxes,
		    int boxn, int flag)
{
    edge_t *uleft, *uright, *lleft, *lright;
    int i, fb, lb;
    splines *spl;
    pointf *pp;
    int pn;

    fb = lb = -1;
    uleft = uright = NULL;
    uleft = top_bound(first, -1), uright = top_bound(first, 1);
    if (uleft) {
	if (!(spl = getsplinepoints(uleft))) return;
	pp = spl->list[0].list;
       	pn = spl->list[0].size;
    }
    if (uright) {
	if (!(spl = getsplinepoints(uright))) return;
	pp = spl->list[0].list;
       	pn = spl->list[0].size;
    }
    lleft = lright = NULL;
    lleft = bot_bound(last, -1), lright = bot_bound(last, 1);
    if (lleft) {
	if (!(spl = getsplinepoints(lleft))) return;
	pp = spl->list[spl->size - 1].list;
       	pn = spl->list[spl->size - 1].size;
    }
    if (lright) {
	if (!(spl = getsplinepoints(lright))) return;
	pp = spl->list[spl->size - 1].list;
       	pn = spl->list[spl->size - 1].size;
    }
    for (i = 0; i < tendp->boxn; i++)
	add_box(P, tendp->boxes[i]);
    fb = P->nbox + 1;
    lb = fb + boxn - 3;
    for (i = 0; i < boxn; i++)
	add_box(P, boxes[i]);
    for (i = hendp->boxn - 1; i >= 0; i--)
	add_box(P, hendp->boxes[i]);
    adjustregularpath(P, fb, lb);
}
