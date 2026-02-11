__dbreg_check_master(env, uid, name)
	ENV *env;
	u_int8_t *uid;
	char *name;
{
	DB *dbp;
	int ret;

	if ((ret = __db_create_internal(&dbp, env, 0)) != 0)
		return (ret);
	F_SET(dbp, DB_AM_RECOVER);
	ret = __db_open(dbp, NULL, NULL,
	    name, NULL, DB_BTREE, 0, DB_MODE_600, PGNO_BASE_MD);

	if (ret == 0 && memcmp(uid, dbp->fileid, DB_FILE_ID_LEN) != 0)
		ret = EINVAL;

	(void)__db_close(dbp, NULL, 0);
	return (ret);
}
