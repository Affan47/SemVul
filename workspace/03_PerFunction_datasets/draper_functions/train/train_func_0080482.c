CDB_memp_fsync(dbmfp)
	DB_MPOOLFILE *dbmfp;
{
	DB_ENV *dbenv;
	DB_MPOOL *dbmp;
	int is_tmp;

	dbmp = dbmfp->dbmp;
	dbenv = dbmp->dbenv;

	PANIC_CHECK(dbenv);


	if (F_ISSET(dbmfp, MP_READONLY))
		return (0);

	R_LOCK(dbenv, &dbmp->reginfo);
	is_tmp = F_ISSET(dbmfp->mfp, MP_TEMP);
	R_UNLOCK(dbenv, &dbmp->reginfo);
	if (is_tmp)
		return (0);

	return (CDB___memp_fsync(dbmfp));
}
