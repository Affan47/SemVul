field_list(DB_DATABASE *db, char *table, char ***fields)
{
#ifdef ODBC_DEBUG_HEADER
fprintf(stderr,"[ODBC][%s][%d]\n",__FILE__,__LINE__);
fprintf(stderr,"\tfield_list\n");
fflush(stderr);
#endif
	SQLSMALLINT colsNum;
	SQLHSTMT statHandle;
	SQLRETURN retcode;

	int i;
	ODBC_CONN *han = (ODBC_CONN *)db->handle;
	ODBC_FIELDS *fieldstr, *current;


	colsNum = 0;
	retcode =
		SQLAllocHandle(SQL_HANDLE_STMT, (ODBC_CONN *) han->odbcHandle, &statHandle);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		return retcode;
	}


	retcode =
		SQLColumns(statHandle, NULL, 0, NULL, 0, (SQLCHAR *) table, SQL_NTS, NULL, 0);


	if (!SQL_SUCCEEDED(retcode))
	{

		SQLFreeHandle(SQL_HANDLE_STMT, statHandle);
		return -1;
	}


	fieldstr = malloc(sizeof(ODBC_FIELDS));

	current = fieldstr;


	while (SQL_SUCCEEDED(SQLFetch(statHandle)))
	{
		if (!SQL_SUCCEEDED
				(SQLGetData
				 (statHandle, SQLColumns_COLUMN_NAME, SQL_C_CHAR, current->fieldname,
					sizeof(current->fieldname), 0)))
			strcpy((char *)current->fieldname, "Unknown");


		colsNum = colsNum + 1;
		current->next = malloc(sizeof(ODBC_FIELDS));
		current = (ODBC_FIELDS *) current->next;
	}

	current = fieldstr;
	GB.NewArray(fields, sizeof(char *), colsNum);

	for (i = 0; i < colsNum; i++)
	{
		(*fields)[i] = GB.NewZeroString((char *) current->fieldname);

		current = (ODBC_FIELDS *) current->next;
		free(fieldstr);
		fieldstr = current;
	}
	free(fieldstr);

	SQLFreeHandle(SQL_HANDLE_STMT, statHandle);


	return colsNum;

}
