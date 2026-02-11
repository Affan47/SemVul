__bamc_compress_idel(dbc, flags)
	DBC *dbc;
	u_int32_t flags;
{
	int ret;
	BTREE_COMPRESS_STREAM stream;
	DB *dbp;
	BTREE_CURSOR *cp;

	COMPQUIET(flags, 0);

	dbp = dbc->dbp;
	cp = (BTREE_CURSOR *)dbc->internal;

	if (F_ISSET(cp, C_COMPRESS_DELETED))
		return DB_KEYEMPTY;
	if (cp->currentKey == 0)
		return DB_NOTFOUND;

	if ((ret = __bam_compress_set_dbt(dbp, &cp->del_key,
		     cp->currentKey->data, cp->currentKey->size)) != 0)
		goto err;
	if ((ret = __bam_compress_set_dbt(dbp, &cp->del_data,
		     cp->currentData->data, cp->currentData->size)) != 0)
		goto err;

	__bam_cs_create_single(&stream, &cp->del_key, &cp->del_data);
	if ((ret = __bamc_compress_merge_delete(dbc, &stream, NULL)) != 0)
		goto err;


	ret = __bamc_compress_get_set(dbc, &cp->del_key, &cp->del_data, 0, 0);
	if (ret == DB_NOTFOUND) {
		__bamc_compress_reset(dbc);
		ret = 0;
	} else if (ret != 0)
		goto err;


	F_SET(cp, C_COMPRESS_DELETED);

 err:
	return (ret);
}
