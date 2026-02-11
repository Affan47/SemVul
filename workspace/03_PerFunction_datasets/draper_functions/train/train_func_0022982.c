CDB___db_dbopen(dbp, name, flags, mode, meta_pgno)
	DB *dbp;
	const char *name;
	u_int32_t flags;
	int mode;
	db_pgno_t meta_pgno;
{
	DB_ENV *dbenv;
	int ret;
	int zero_length;

	dbenv = dbp->dbenv;


	if ((ret = CDB___db_file_setup(dbp,
	    name, flags, mode, meta_pgno, &zero_length)) != 0)
		return (ret);


	if ((ret = CDB___db_dbenv_setup(dbp, name, flags)) != 0)
		return (ret);


	F_SET(dbp, DB_OPEN_CALLED);

	if (zero_length)
		return (0);

	switch (dbp->type) {
	case DB_BTREE:
		ret = CDB___bam_open(dbp, name, meta_pgno);
		break;
	case DB_HASH:
		ret = CDB___ham_open(dbp, name, meta_pgno);
		break;
	case DB_RECNO:
		ret = CDB___ram_open(dbp, name, meta_pgno);
		break;
	case DB_QUEUE:
		ret = CDB___qam_open(dbp, name, meta_pgno);
		break;
	case DB_UNKNOWN:
		ret = EINVAL;
		break;
	}
	return (ret);
}
