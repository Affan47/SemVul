__dbc_put_arg(dbc, key, data, flags)
	DBC *dbc;
	DBT *key, *data;
	u_int32_t flags;
{
	DB *dbp;
	ENV *env;
	int key_flags, ret;

	dbp = dbc->dbp;
	env = dbp->env;
	key_flags = 0;


	if (DB_IS_READONLY(dbp))
		return (__db_rdonly(env, "DBcursor->put"));


	if (F_ISSET(dbp, DB_AM_SECONDARY)) {
		if (flags == DB_UPDATE_SECONDARY)
			flags = 0;
		else {
			__db_errx(env, DB_STR("0628",
			    "DBcursor->put forbidden on secondary indices"));
			return (EINVAL);
		}
	}

	if ((ret = __dbt_usercopy(env, data)) != 0)
		return (ret);


	switch (flags) {
	case DB_AFTER:
	case DB_BEFORE:
		switch (dbp->type) {
		case DB_BTREE:
		case DB_HASH:
			if (!F_ISSET(dbp, DB_AM_DUP))
				goto err;
			if (dbp->dup_compare != NULL)
				goto err;
			break;
		case DB_QUEUE:
			goto err;
		case DB_RECNO:
			if (!F_ISSET(dbp, DB_AM_RENUMBER))
				goto err;
			key_flags = key == NULL ? 0 : 1;
			break;
		case DB_UNKNOWN:
		default:
			goto err;
		}
		break;
	case DB_CURRENT:


		break;
	case DB_NODUPDATA:
		if (!F_ISSET(dbp, DB_AM_DUPSORT))
			goto err;

	case DB_KEYFIRST:
	case DB_KEYLAST:
	case DB_OVERWRITE_DUP:
		key_flags = 1;
		if ((ret = __dbt_usercopy(env, key)) != 0)
			return (ret);
		break;
	default:
err:		return (__db_ferr(env, "DBcursor->put", 0));
	}


	if (key_flags && (ret = __dbt_ferr(dbp, "key", key, 0)) != 0)
		return (ret);
	if ((ret = __dbt_ferr(dbp, "data", data, 0)) != 0)
		return (ret);


	if (key_flags && F_ISSET(key, DB_DBT_PARTIAL) && key->dlen != 0)
		return (__db_ferr(env, "key DBT", 0));


	if (!IS_INITIALIZED(dbc) && flags != 0 && flags != DB_KEYFIRST &&
	    flags != DB_KEYLAST && flags != DB_NODUPDATA &&
	    flags != DB_OVERWRITE_DUP)
		return (__db_curinval(env));

	return (0);
}
