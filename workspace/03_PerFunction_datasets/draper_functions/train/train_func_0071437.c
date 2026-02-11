dbmnydec(DBPROCESS * dbproc, DBMONEY * amount)
{
	tdsdump_log(TDS_DBG_FUNC, "dbmnydec(%p, %p)\n", dbproc, amount);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_NULP(amount, "dbmnydec", 2, FAIL);

	if (amount->mnylow != 0) {
		--amount->mnylow;
		return SUCCEED;
	}
	if (amount->mnyhigh == -0x80000000l)
		return FAIL;
	amount->mnylow = 0xFFFFFFFFlu;
	--amount->mnyhigh;
	return SUCCEED;
}
