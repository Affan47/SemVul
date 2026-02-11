CDB___dbenv_refresh(dbenv)
	DB_ENV *dbenv;
{
	int ret, t_ret;
	char **p;

	ret = 0;


	if (dbenv->tx_handle != NULL) {
		if ((t_ret = CDB___txn_close(dbenv)) != 0 && ret == 0)
			ret = t_ret;
		dbenv->tx_handle = NULL;
	}

	if (dbenv->lk_handle != NULL) {
		if ((t_ret = CDB___lock_close(dbenv)) != 0 && ret == 0)
			ret = t_ret;
		dbenv->lk_handle = NULL;
	}
	CDB___lock_dbenv_close(dbenv);

	if (dbenv->lg_handle != NULL) {
		if ((t_ret = CDB___log_close(dbenv)) != 0 && ret == 0)
			ret = t_ret;
		dbenv->lg_handle = NULL;
	}

	if (dbenv->mp_handle != NULL) {
		if ((t_ret = CDB___memp_close(dbenv)) != 0 && ret == 0)
			ret = t_ret;
		dbenv->mp_handle = NULL;
	}


	if (dbenv->reginfo != NULL) {
		if ((t_ret = CDB___db_e_detach(dbenv, 0)) != 0 && ret == 0)
			ret = t_ret;


	}


	dbenv->db_panic = 0;

	if (dbenv->db_home != NULL) {
		CDB___os_freestr(dbenv->db_home);
		dbenv->db_home = NULL;
	}
	if (dbenv->db_log_dir != NULL) {
		CDB___os_freestr(dbenv->db_log_dir);
		dbenv->db_log_dir = NULL;
	}
	if (dbenv->db_tmp_dir != NULL) {
		CDB___os_freestr(dbenv->db_tmp_dir);
		dbenv->db_tmp_dir = NULL;
	}
	if (dbenv->db_data_dir != NULL) {
		for (p = dbenv->db_data_dir; *p != NULL; ++p)
			CDB___os_freestr(*p);
		CDB___os_free(dbenv->db_data_dir,
		    dbenv->data_cnt * sizeof(char **));
		dbenv->db_data_dir = NULL;
	}
	dbenv->data_cnt = dbenv->data_next = 0;

	dbenv->db_mode = 0;

	if (dbenv->lockfhp != NULL) {
		CDB___os_free(dbenv->lockfhp, sizeof(*dbenv->lockfhp));
		dbenv->lockfhp = NULL;
	}

	if (dbenv->dtab != NULL) {
		CDB___os_free(dbenv->dtab,
		    dbenv->dtab_size * sizeof(dbenv->dtab[0]));
		dbenv->dtab = NULL;
		dbenv->dtab_size = 0;
	}

	dbenv->mp_mmapsize = 0;
	dbenv->links.tqe_next = NULL;
	dbenv->links.tqe_prev = NULL;
	dbenv->xa_rmid = 0;
	dbenv->xa_txn = 0;

	F_CLR(dbenv, ~(DB_ENV_STANDALONE | DB_ENV_USER_ALLOC));

	return (ret);
}
