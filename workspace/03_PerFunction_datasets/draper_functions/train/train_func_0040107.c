fh_extractminel(struct fibheap *h)
{
	struct fibheap_el *ret;
	struct fibheap_el *x, *y, *orig;

	ret = h->fh_min;

	orig = NULL;


	for(x = ret->fhe_child; x != orig && x != NULL;) {
		if (orig == NULL)
			orig = x;
		y = x->fhe_right;
		x->fhe_p = NULL;
		fh_insertrootlist(h, x);
		x = y;
	}

	fh_removerootlist(h, ret);
	h->fh_n--;


	if (h->fh_n == 0)
		h->fh_min = NULL;
	else {
		h->fh_min = ret->fhe_right;
		fh_consolidate(h);
	}

#ifdef FH_STATS
	h->fh_nextracts++;
#endif

	return ret;
}
