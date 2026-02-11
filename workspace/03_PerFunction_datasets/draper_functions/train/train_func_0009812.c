SQLSetStmtAttr(SQLHSTMT hstmt, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	tdsdump_log(TDS_DBG_FUNC, "SQLSetStmtAttr(%p, %d, %p, %d)\n",
			hstmt, (int)Attribute, ValuePtr, (int)StringLength);

	return _SQLSetStmtAttr(hstmt, Attribute, ValuePtr, StringLength);
}
