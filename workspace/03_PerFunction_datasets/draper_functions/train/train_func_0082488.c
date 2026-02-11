CDB___lock_open(dbenv)
	DB_ENV *dbenv;
{
	DB_LOCKREGION *region;
	DB_LOCKTAB *lt;
	size_t size;
	int ret;


	if ((ret = CDB___os_calloc(1, sizeof(DB_LOCKTAB), &lt)) != 0)
		return (ret);
	lt->dbenv = dbenv;


	lt->reginfo.id = REG_ID_LOCK;
	lt->reginfo.mode = dbenv->db_mode;
	if (F_ISSET(dbenv, DB_ENV_CREATE))
		F_SET(&lt->reginfo, REGION_CREATE_OK);
	size = CDB___lock_region_size(dbenv);
	if ((ret = CDB___db_r_attach(dbenv, &lt->reginfo, size)) != 0)
		goto err;


	if (F_ISSET(&lt->reginfo, REGION_CREATE))
		if ((ret = CDB___lock_init(dbenv, lt)) != 0)
			goto err;


	region = lt->reginfo.primary =
	    R_ADDR(&lt->reginfo, lt->reginfo.rp->primary);


	if (dbenv->lk_detect != DB_LOCK_NORUN) {
		if (region->detect != DB_LOCK_NORUN &&
		    dbenv->lk_detect != DB_LOCK_DEFAULT &&
		    region->detect != dbenv->lk_detect) {
			CDB___db_err(dbenv,
		    "lock_open: incompatible deadlock detector mode");
			ret = EINVAL;
			goto err;
		}


		if (region->detect == DB_LOCK_NORUN)
			region->detect = dbenv->lk_detect;
	}


	lt->memlock = (MUTEX *)R_ADDR(&lt->reginfo, region->memlock_off);
	lt->conflicts = (u_int8_t *)R_ADDR(&lt->reginfo, region->conf_off);
	lt->obj_tab = (DB_HASHTAB *)R_ADDR(&lt->reginfo, region->obj_off);
	lt->osynch_tab = (MUTEX *)R_ADDR(&lt->reginfo, region->osynch_off);
	lt->locker_tab = (DB_HASHTAB *)R_ADDR(&lt->reginfo, region->locker_off);
	lt->lsynch_tab = (MUTEX *)R_ADDR(&lt->reginfo, region->lsynch_off);

	R_UNLOCK(dbenv, &lt->reginfo);

	dbenv->lk_handle = lt;
	return (0);

err:	if (lt->reginfo.addr != NULL) {
		if (F_ISSET(&lt->reginfo, REGION_CREATE))
			F_SET(lt->reginfo.rp, REG_DEAD);
		R_UNLOCK(dbenv, &lt->reginfo);
		(void)CDB___db_r_detach(dbenv, &lt->reginfo, 0);
	}
	CDB___os_free(lt, sizeof(*lt));
	return (ret);
}
