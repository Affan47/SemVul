ckh_grow(ckh_t *ckh)
{
	bool ret;
	ckhc_t *tab, *ttab;
	size_t lg_curcells;
	unsigned lg_prevbuckets;

#ifdef CKH_COUNT
	ckh->ngrows++;
#endif


	lg_prevbuckets = ckh->lg_curbuckets;
	lg_curcells = ckh->lg_curbuckets + LG_CKH_BUCKET_CELLS;
	while (true) {
		size_t usize;

		lg_curcells++;
		usize = sa2u(sizeof(ckhc_t) << lg_curcells, CACHELINE);
		if (usize == 0) {
			ret = true;
			goto label_return;
		}
		tab = (ckhc_t *)ipalloc(usize, CACHELINE, true);
		if (tab == NULL) {
			ret = true;
			goto label_return;
		}

		ttab = ckh->tab;
		ckh->tab = tab;
		tab = ttab;
		ckh->lg_curbuckets = lg_curcells - LG_CKH_BUCKET_CELLS;

		if (ckh_rebuild(ckh, tab) == false) {
			idalloc(tab);
			break;
		}


		idalloc(ckh->tab);
		ckh->tab = tab;
		ckh->lg_curbuckets = lg_prevbuckets;
	}

	ret = false;
label_return:
	return (ret);
}
