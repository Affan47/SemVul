reorder_invent()
{
	struct obj *otmp, *prev, *next;
	boolean need_more_sorting;

	do {


	    need_more_sorting = FALSE;
	    for (otmp = invent, prev = 0; otmp; ) {
		next = otmp->nobj;
		if (next && inv_rank(next) < inv_rank(otmp)) {
		    need_more_sorting = TRUE;
		    if (prev) prev->nobj = next;
		    else      invent = next;
		    otmp->nobj = next->nobj;
		    next->nobj = otmp;
		    prev = next;
		} else {
		    prev = otmp;
		    otmp = next;
		}
	    }
	} while (need_more_sorting);
}
