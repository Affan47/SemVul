CDB___db_cgetchk(dbp, key, data, flags, isvalid)
	const DB *dbp;
	DBT *key, *data;
	u_int32_t flags;
	int isvalid;
{
	int key_einval, key_flags, ret;

	key_einval = key_flags = 0;


	if (LF_ISSET(DB_RMW)) {
		if (!F_ISSET(dbp->dbenv, DB_ENV_LOCKING)) {
			CDB___db_err(dbp->dbenv,
			    "the DB_RMW flag requires locking");
			return (EINVAL);
		}
		LF_CLR(DB_RMW);
	}


	switch (flags) {
	case DB_NEXT_DUP:
		if (dbp->type == DB_RECNO || dbp->type == DB_QUEUE)
			goto err;

	case DB_CURRENT:
	case DB_FIRST:
	case DB_LAST:
	case DB_NEXT:
	case DB_PREV:
		key_flags = 1;
		break;
	case DB_GET_BOTH:
		if (dbp->type == DB_RECNO || dbp->type == DB_QUEUE)
			goto err;

	case DB_SET_RANGE:
		key_einval = key_flags = 1;
		break;
	case DB_SET:
		key_einval = 1;
		break;
	case DB_GET_RECNO:
		if (!F_ISSET(dbp, DB_BT_RECNUM))
			goto err;
		break;
	case DB_SET_RECNO:
		if (!F_ISSET(dbp, DB_BT_RECNUM))
			goto err;
		key_einval = key_flags = 1;
		break;
	case DB_CONSUME:
		if (dbp->type == DB_QUEUE)
			break;

	default:
err:		return (CDB___db_ferr(dbp->dbenv, "DBcursor->c_get", 0));
	}


	if ((ret = CDB___dbt_ferr(dbp, "key", key, 0)) != 0)
		return (ret);
	if ((ret = CDB___dbt_ferr(dbp, "data", data, 0)) != 0)
		return (ret);


	if (key_einval && (key->data == NULL || key->size == 0))
		return (CDB___db_keyempty(dbp->dbenv));


	return (isvalid ||
	    (flags != DB_CURRENT && flags != DB_NEXT_DUP) ? 0 : EINVAL);
}
