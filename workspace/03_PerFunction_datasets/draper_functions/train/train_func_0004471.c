SQLFreeStmt(SQLHSTMT hstmt, SQLUSMALLINT fOption)
{
	tdsdump_log(TDS_DBG_FUNC, "SQLFreeStmt(%p, %d)\n", hstmt, fOption);
	return _SQLFreeStmt(hstmt, fOption, 0);
}
