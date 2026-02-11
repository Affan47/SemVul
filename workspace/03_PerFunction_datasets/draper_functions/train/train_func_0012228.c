__bamc_compress_get_multiple_key(dbc, data, flags)
	DBC *dbc;
	DBT *data;
	u_int32_t flags;
{
	int ret;
	u_int8_t *writekey, *writedata;
	void *mptr;
	BTREE_CURSOR *cp;

	ret = 0;
	cp = (BTREE_CURSOR *)dbc->internal;

	DB_MULTIPLE_WRITE_INIT(mptr, data);
	DB_MULTIPLE_KEY_RESERVE_NEXT(mptr, data, writekey, cp->currentKey->size,
		writedata, cp->currentData->size);
	if (writekey == NULL) {
		data->size = cp->currentKey->size + cp->currentData->size +
			4 * sizeof(u_int32_t);
		return DB_BUFFER_SMALL;
	}
	DB_ASSERT(dbc->dbp->env, writedata != NULL);

	memcpy(writekey, cp->currentKey->data, cp->currentKey->size);
	memcpy(writedata, cp->currentData->data, cp->currentData->size);

	while ((ret = __bamc_compress_get_next(dbc, flags)) == 0) {
		DB_MULTIPLE_KEY_RESERVE_NEXT(mptr, data, writekey,
		    cp->currentKey->size, writedata, cp->currentData->size);
		if (writekey == NULL)
			break;
		DB_ASSERT(dbc->dbp->env, writedata != NULL);


		memcpy(writekey, cp->currentKey->data, cp->currentKey->size);
		memcpy(writedata, cp->currentData->data, cp->currentData->size);
	}

	if (ret == DB_NOTFOUND)
		ret = 0;

	if (ret == 0)


		ret = __bamc_compress_get_prev(dbc, flags);

	return (ret);
}
