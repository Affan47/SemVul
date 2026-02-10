dbchange(DBPROCESS * dbproc)
{
	tdsdump_log(TDS_DBG_FUNC, "dbchange(%p)\n", dbproc);
	CHECK_PARAMETER(dbproc, SYBENULL, NULL);

	if (dbproc->envchange_rcv & (1 << (TDS_ENV_DATABASE - 1))) {
		return dbproc->dbcurdb;
	}
	return NULL;
}
