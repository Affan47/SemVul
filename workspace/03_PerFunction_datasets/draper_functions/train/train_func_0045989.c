__get_filereg_by_dbregid(lvinfo, dbregid, freginfopp)
	const DB_LOG_VRFY_INFO *lvinfo;
	int32_t dbregid;
	VRFY_FILEREG_INFO **freginfopp;
{
	int ret;
	DBT key, data;
	char uid[DB_FILE_ID_LEN];
	VRFY_FILELIFE *pflife;

	memset(&data, 0, sizeof(DBT));
	memset(&key, 0, sizeof(DBT));
	key.data = &dbregid;
	key.size = sizeof(dbregid);

	BDBOP3(lvinfo->dbenv, __db_get(lvinfo->dbregids, lvinfo->ip, NULL,
	    &key, &data, 0), DB_NOTFOUND,  "__get_filereg_by_dbregid");
	if (ret == DB_NOTFOUND)
		goto err;


	pflife = (VRFY_FILELIFE *)data.data;
	memcpy((void *)uid, (void *)pflife->fileid, key.size = DB_FILE_ID_LEN);

	key.data = (void *)uid;
	memset(&data, 0, sizeof(DBT));

	BDBOP3(lvinfo->dbenv, __db_get(lvinfo->fileregs, lvinfo->ip, NULL,
	    &key, &data, 0), DB_NOTFOUND,  "__get_filereg_by_dbregid");
	if (ret == DB_NOTFOUND)
		goto err;
	if ((ret = __lv_unpack_filereg(&data, freginfopp)) != 0)
		goto err;

err:
	return (ret);
}
