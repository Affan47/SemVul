CDB___memp_dumpcache(dbmp, reginfo, fmap, fp, flags)
	DB_MPOOL *dbmp;
	REGINFO *reginfo;
	size_t *fmap;
	FILE *fp;
	u_int32_t flags;
{
	BH *bhp;
	DB_HASHTAB *dbht;
	MCACHE *mc;
	int bucket;

	mc = reginfo->primary;


	if (LF_ISSET(MPOOL_DUMP_HASH)) {
		(void)fprintf(fp,
	    "%s\nBH hash table (%lu hash slots)\npageno, file, ref, address\n",
		    DB_LINE, (u_long)mc->htab_buckets);
		for (dbht = R_ADDR(reginfo, mc->htab),
		    bucket = 0; bucket < mc->htab_buckets; ++dbht, ++bucket) {
			if (SH_TAILQ_FIRST(dbht, __bh) != NULL)
				(void)fprintf(fp, "%lu:\n", (u_long)bucket);
			for (bhp = SH_TAILQ_FIRST(dbht, __bh);
			    bhp != NULL; bhp = SH_TAILQ_NEXT(bhp, hq, __bh))
				CDB___memp_pbh(dbmp, bhp, fmap, fp);
		}
	}


	if (LF_ISSET(MPOOL_DUMP_LRU)) {
		(void)fprintf(fp, "%s\nBH LRU list\n", DB_LINE);
		(void)fprintf(fp, "pageno, file, ref, address\n");
		for (bhp = SH_TAILQ_FIRST(&mc->bhq, __bh);
		    bhp != NULL; bhp = SH_TAILQ_NEXT(bhp, q, __bh))
			CDB___memp_pbh(dbmp, bhp, fmap, fp);
	}
}
