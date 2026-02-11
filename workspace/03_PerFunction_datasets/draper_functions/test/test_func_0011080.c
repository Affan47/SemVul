SQLGetConnectOption(SQLHDBC hdbc, SQLUSMALLINT fOption, SQLPOINTER pvParam)
{
	tdsdump_log(TDS_DBG_FUNC, "SQLGetConnectOption(%p, %u, %p)\n", hdbc, fOption, pvParam);

	return _SQLGetConnectAttr(hdbc, (SQLINTEGER) fOption, pvParam, SQL_MAX_OPTION_STRING_LENGTH, NULL _wide0);
}
