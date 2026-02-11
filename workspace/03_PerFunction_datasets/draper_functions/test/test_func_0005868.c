__bam_set_bt_compress(dbp, compress, decompress)
	DB *dbp;
	int (*compress) __P((DB *, const DBT *, const DBT *, const DBT *,
				    const DBT *, DBT *));
	int (*decompress) __P((DB *, const DBT *, const DBT *, DBT *, DBT *,
				      DBT *));
{
#ifdef HAVE_COMPRESSION
	BTREE *t;

	DB_ILLEGAL_AFTER_OPEN(dbp, "DB->set_bt_compress");
	DB_ILLEGAL_METHOD(dbp, DB_OK_BTREE);

	t = dbp->bt_internal;


	if (F_ISSET(dbp, DB_AM_RECNUM)) {
		__db_errx(dbp->env, DB_STR("1027",
		    "compression cannot be used with DB_RECNUM"));
		return (EINVAL);
	}


	if (F_ISSET(dbp, DB_AM_DUP) && !F_ISSET(dbp, DB_AM_DUPSORT)) {
		__db_errx(dbp->env, DB_STR("1028",
	    "compression cannot be used with DB_DUP without DB_DUPSORT"));
		return (EINVAL);
	}


	if (dbp->blob_threshold > 0) {
		__db_errx(dbp->env, DB_STR("1198",
		    "compression cannot be used with blobs enabled."));
		return (EINVAL);
	}

	if (compress != 0 && decompress != 0) {
		t->bt_compress = compress;
		t->bt_decompress = decompress;
	} else if (compress == 0 && decompress == 0) {
		t->bt_compress = __bam_defcompress;
		t->bt_decompress = __bam_defdecompress;
	} else {
		__db_errx(dbp->env, DB_STR("1029",
    "to enable compression you need to supply both function arguments"));
		return (EINVAL);
	}
	F_SET(dbp, DB_AM_COMPRESS);


	if (F_ISSET(dbp, DB_AM_DUPSORT)) {
		t->compress_dup_compare = dbp->dup_compare;
		dbp->dup_compare = __bam_compress_dupcmp;
	}

	return (0);
#else
	COMPQUIET(compress, NULL);
	COMPQUIET(decompress, NULL);

	__db_errx(dbp->env, DB_STR("1030",
	    "compression support has not been compiled in"));
	return (EINVAL);
#endif
}
