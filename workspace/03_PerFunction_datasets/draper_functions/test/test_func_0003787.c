get_num_columns(ODBC_RESULT *result)
{
	SQLSMALLINT colsNum = 0;
	SQLRETURN retcode;

	retcode = SQLNumResultCols(result->odbcStatHandle, &colsNum);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
		GB.Error("ODBC error: Unable to get the number of columns");

	return colsNum;
}
