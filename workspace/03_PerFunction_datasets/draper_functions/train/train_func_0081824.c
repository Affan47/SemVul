rc_avpair_copy(VALUE_PAIR *p)
{
	VALUE_PAIR *vp, *fp = NULL, *lp = NULL;

	while (p) {
		vp = malloc(sizeof(VALUE_PAIR));
		if (!vp) {
		    novm("rc_avpair_copy");
		    return NULL;
		}
		*vp = *p;
		if (!fp)
			fp = vp;
		if (lp)
			lp->next = vp;
		lp = vp;
		p = p->next;
	}

	return fp;
}
