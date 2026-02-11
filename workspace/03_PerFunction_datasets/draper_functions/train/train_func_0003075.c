dbrows(DBPROCESS * dbproc)
{
	TDSSOCKET *tds;

	tdsdump_log(TDS_DBG_FUNC, "dbrows(%p)\n", dbproc);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);

	if (!(tds=dbproc->tds_socket))
		return FAIL;

	return (tds->res_info && tds->res_info->rows_exist)? SUCCEED : FAIL;
}
