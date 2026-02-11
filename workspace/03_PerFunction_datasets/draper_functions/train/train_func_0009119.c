listelement(LIST *lp, long index)
{
	register LISTELEM *ep;
	long dist;
	long temp;
	BOOL forward;

	if (index < 0)
		index += lp->l_count;
	if ((index < 0) || (index >= lp->l_count))
		return NULL;


	if (index == 0)
		return lp->l_first;
	if (index == 1)
		return lp->l_first->e_next;
	if (index == lp->l_count - 1)
		return lp->l_last;
	if ((index == lp->l_cacheindex) && lp->l_cache)
		return lp->l_cache;


	forward = ((index * 2) <= lp->l_count);
	if (forward) {
		dist = index;
		ep = lp->l_first;
	} else {
		dist = (lp->l_count - 1) - index;
		ep = lp->l_last;
	}


	if (lp->l_cache) {
		temp = index - lp->l_cacheindex;
		if ((temp >= 0) && (temp < dist)) {
			dist = temp;
			ep = lp->l_cache;
			forward = TRUE;
		}
		if ((temp < 0) && (-temp < dist)) {
			dist = -temp;
			ep = lp->l_cache;
			forward = FALSE;
		}
	}


	if (forward) {
		while (dist-- > 0)
			ep = ep->e_next;
	} else {
		while (dist-- > 0)
			ep = ep->e_prev;
	}
	lp->l_cache = ep;
	lp->l_cacheindex = index;
	return ep;
}
