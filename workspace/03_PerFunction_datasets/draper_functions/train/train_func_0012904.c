__db_log_verify_global_report (lvinfo)
	const DB_LOG_VRFY_INFO *lvinfo;
{
	u_int32_t i, nltype;

	__db_msg(lvinfo->dbenv->env,
	    "Number of active transactions: %u;", lvinfo->ntxn_active);
	__db_msg(lvinfo->dbenv->env,
	    "Number of committed transactions: %u;", lvinfo->ntxn_commit);
	__db_msg(lvinfo->dbenv->env,
	    "Number of aborted transactions: %u;", lvinfo->ntxn_abort);
	__db_msg(lvinfo->dbenv->env,
	    "Number of prepared transactions: %u;", lvinfo->ntxn_prep);
	__db_msg(lvinfo->dbenv->env,
	    "Total number of checkpoint: %u;", lvinfo->nckp);
	__db_msg(lvinfo->dbenv->env,
	    "Total number of non-transactional updates: %u;",
	    lvinfo->non_txnup_cnt);
	__db_msg(lvinfo->dbenv->env,
	    "Total number of unknown log records: %u;",
	    lvinfo->unknown_logrec_cnt);
	__db_msg(lvinfo->dbenv->env,
	    "Total number of app-specific log record: %u;",
	    lvinfo->external_logrec_cnt);
	__db_msg(lvinfo->dbenv->env,
	    "The number of each type of log record:");

	for (i = 0; i < 256; i++) {
		nltype = lvinfo->lrtypes[i];
		if (LOGTYPE_NAME(lvinfo, i) != NULL)
			__db_msg(lvinfo->dbenv->env, "\n\t%s : %u;",
			    LOGTYPE_NAME(lvinfo, i), nltype);
	}
}
