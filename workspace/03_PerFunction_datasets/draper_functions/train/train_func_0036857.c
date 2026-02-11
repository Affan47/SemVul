__bam_get_bt_compress(dbp, compressp, decompressp)
	DB *dbp;
	int (**compressp) __P((DB *, const DBT *, const DBT *, const DBT *,
				      const DBT *, DBT *));
	int (**decompressp) __P((DB *, const DBT *, const DBT *, DBT *, DBT *,
					DBT *));
{
#ifdef HAVE_COMPRESSION
	BTREE *t;

	DB_ILLEGAL_METHOD(dbp, DB_OK_BTREE);

	t = dbp->bt_internal;

	if (compressp != NULL)
		*compressp = t->bt_compress;
	if (decompressp != NULL)
		*decompressp = t->bt_decompress;

	return (0);
#else
	COMPQUIET(compressp, NULL);
	COMPQUIET(decompressp, NULL);

	__db_errx(dbp->env, DB_STR("1026",
	    "compression support has not been compiled in"));
	return (EINVAL);
#endif
}
