CDB___memp_bhfree(dbmp, bhp, free_mem)
	DB_MPOOL *dbmp;
	BH *bhp;
	int free_mem;
{
	DB_HASHTAB *dbht;
	MCACHE *mc;
	MPOOL *mp;
	int n_bucket, n_cache;

	mp = dbmp->reginfo.primary;
	mc = BH_TO_CACHE(dbmp, bhp);
	n_cache = NCACHE(mp, bhp->pgno);
	n_bucket = NBUCKET(mc, bhp->mf_offset, bhp->pgno);
	dbht = R_ADDR(&dbmp->c_reginfo[n_cache], mc->htab);


	SH_TAILQ_REMOVE(&dbht[n_bucket], bhp, hq, __bh);


	SH_TAILQ_REMOVE(&mc->bhq, bhp, q, __bh);

	DB_ASSERT(mc->stat.st_page_clean != 0);
	--mc->stat.st_page_clean;


	       CDB___memp_cmpr_free_chain(dbmp, bhp);
	if (free_mem) {
	       CDB___db_shalloc_free(dbmp->c_reginfo[n_cache].addr, bhp);
	}
}
