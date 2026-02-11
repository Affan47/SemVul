CDB___lock_dbenv_close(dbenv)
	DB_ENV *dbenv;
{
	if (!F_ISSET(dbenv, DB_ENV_USER_ALLOC) && dbenv->lk_conflicts != NULL) {
		CDB___os_free(dbenv->lk_conflicts,
		    dbenv->lk_modes * dbenv->lk_modes);
		dbenv->lk_conflicts = NULL;
	}
}
