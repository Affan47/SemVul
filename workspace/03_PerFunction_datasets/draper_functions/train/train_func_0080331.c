ckh_new(ckh_t *ckh, size_t minitems, ckh_hash_t *hash, ckh_keycomp_t *keycomp)
{
	bool ret;
	size_t mincells, usize;
	unsigned lg_mincells;

	assert(minitems > 0);
	assert(hash != NULL);
	assert(keycomp != NULL);

#ifdef CKH_COUNT
	ckh->ngrows = 0;
	ckh->nshrinks = 0;
	ckh->nshrinkfails = 0;
	ckh->ninserts = 0;
	ckh->nrelocs = 0;
#endif
	ckh->prn_state = 42;
	ckh->count = 0;


	assert(LG_CKH_BUCKET_CELLS > 0);
	mincells = ((minitems + (3 - (minitems % 3))) / 3) << 2;
	for (lg_mincells = LG_CKH_BUCKET_CELLS;
	    (ZU(1) << lg_mincells) < mincells;
	    lg_mincells++)
		;
	ckh->lg_minbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->lg_curbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->hash = hash;
	ckh->keycomp = keycomp;

	usize = sa2u(sizeof(ckhc_t) << lg_mincells, CACHELINE, NULL);
	if (usize == 0) {
		ret = true;
		goto RETURN;
	}
	ckh->tab = (ckhc_t *)ipalloc(usize, CACHELINE, true);
	if (ckh->tab == NULL) {
		ret = true;
		goto RETURN;
	}

#ifdef JEMALLOC_DEBUG
	ckh->magic = CKH_MAGIC;
#endif

	ret = false;
RETURN:
	return (ret);
}
