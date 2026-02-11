dbisopt(DBPROCESS * dbproc, int option, const char param[])
{
	tdsdump_log(TDS_DBG_FUNC, "dbisopt(%p, %d, %s)\n", dbproc, option, param);
	CHECK_PARAMETER(dbproc, SYBENULL, FALSE);


	if ((option < 0) || (option >= DBNUMOPTIONS)) {
		return FALSE;
	}
	return dbproc->dbopts[option].factive;
}
