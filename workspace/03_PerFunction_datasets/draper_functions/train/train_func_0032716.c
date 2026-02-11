lhash_delete(lhash_t* lh)
{
    lhash_bucket_t*** sp = lh->seg;
    int n = lh->nsegs;

    while(n--) {
	lhash_bucket_t** bp = *sp;
	if (bp != 0) {
	    int m = LHASH_SEGSZ;
	    while(m--) {
		lhash_bucket_t* p = *bp++;
		while(p != 0) {
		    lhash_bucket_t* next = p->next;
		    if (lh->func.release)
			lh->func.release((void*) p);
		    p = next;
		}
	    }
	    free(*sp);
	}
	sp++;
    }
    free(lh->seg);

    if (lh->is_allocated)
	free(lh);
}
