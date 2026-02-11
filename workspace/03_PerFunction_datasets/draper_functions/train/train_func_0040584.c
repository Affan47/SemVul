dump_sub(DB *parent_dbp, char *parent_name, int pflag, int keyflag)
{
	DB *dbp;
	DBC *dbcp;
	DBT key, data;
	int ret;
	char *subdb;


	if ((ret = parent_dbp->cursor(parent_dbp, NULL, &dbcp, 0)) != 0) {
		dbenv->err(dbenv, ret, "DB->cursor");
		return (1);
	}

	memset(&key, 0, sizeof(key));
	memset(&data, 0, sizeof(data));
	while ((ret = dbcp->c_get(dbcp, &key, &data, DB_NEXT)) == 0) {

		if ((subdb = (char*)malloc(key.size + 1)) == NULL) {
			dbenv->err(dbenv, ENOMEM, NULL);
			return (1);
		}
		memcpy(subdb, key.data, key.size);
		subdb[key.size] = '\0';


		if ((ret = CDB_db_create(&dbp, dbenv, 0)) != 0) {
			dbenv->err(dbenv, ret, "CDB_db_create");
			free(subdb);
			return (1);
		}
		if ((ret = dbp->open(dbp,
		    parent_name, subdb, DB_UNKNOWN, DB_RDONLY, 0)) != 0)
			dbp->err(dbp, ret,
			    "DB->open: %s:%s", parent_name, subdb);
		if (ret == 0 &&
		    (pheader(dbp, subdb, pflag, keyflag) ||
		    dump(dbp, pflag, keyflag)))
			ret = 1;
		(void)dbp->close(dbp, 0);
		free(subdb);
		if (ret != 0)
			return (1);
	}
	if (ret != DB_NOTFOUND) {
		dbp->err(dbp, ret, "DBcursor->get");
		return (1);
	}

	if ((ret = dbcp->c_close(dbcp)) != 0) {
		dbp->err(dbp, ret, "DBcursor->close");
		return (1);
	}

	return (0);
}
