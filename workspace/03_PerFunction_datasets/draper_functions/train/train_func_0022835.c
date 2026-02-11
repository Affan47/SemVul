table_init(DB_DATABASE *db, char *table, DB_INFO * info)
{
#ifdef ODBC_DEBUG_HEADER
fprintf(stderr,"[ODBC][%s][%d]\n",__FILE__,__LINE__);
fprintf(stderr,"\ttable_init\n");
fflush(stderr);
#endif
	SQLCHAR coltype[100];
	SQLCHAR precision[100];
	SQLSMALLINT colsNum;
	SQLHSTMT statHandle;

	SQLRETURN retcode;
	int i;
	DB_FIELD *f;
	ODBC_FIELDS *fieldstr, *current;
	ODBC_CONN *han = (ODBC_CONN *)db->handle;


	info->table = GB.NewZeroString(table);

	retcode =SQLAllocHandle(SQL_HANDLE_STMT, (ODBC_CONN *) han->odbcHandle, &statHandle);


	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		return retcode;
	}

	if (!SQL_SUCCEEDED
			(colsNum =
			 SQLColumns(statHandle, NULL, 0, NULL, 0, (SQLCHAR *) table, SQL_NTS, NULL,
									0)))
		return -1;

	fieldstr = malloc(sizeof(ODBC_FIELDS));
	current = fieldstr;

	colsNum = 0;
	while (SQL_SUCCEEDED(SQLFetch(statHandle)))
	{
		SQLGetData(statHandle, SQLColumns_COLUMN_NAME, SQL_C_CHAR, current->fieldname,
							 sizeof(current->fieldname), 0);

		if (!SQL_SUCCEEDED
				(SQLGetData
				 (statHandle, SQLColumns_SQL_DATA_TYPE, SQL_C_CHAR, &coltype[0],
					sizeof(coltype), 0)))
			return TRUE;

		current->type = atol((char *)coltype);

		if (!SQL_SUCCEEDED
				(SQLGetData
				 (statHandle, SQLColumns_COLUMN_SIZE, SQL_C_CHAR, precision,
					sizeof(precision), 0)))
			return TRUE;

		current->outlen = atol((char *)precision);
		colsNum = colsNum + 1;
		current->next = malloc(sizeof(ODBC_FIELDS));
		current = (ODBC_FIELDS *) current->next;
	}

	info->nfield = colsNum;
	GB.Alloc(POINTER(&info->field), sizeof(DB_FIELD) * colsNum);
	i = 0;
	current = fieldstr;

	for (i = 0; i < colsNum; i++)
	{
		fieldstr = current;
		f = &info->field[i];
		f->name = GB.NewZeroString((char *)current->fieldname);

		f->type = conv_type(current->type);

		f->length = 0;
		if (f->type == GB_T_STRING)
			f->length = current->outlen;
		free(fieldstr);
		current = (ODBC_FIELDS *) current->next;
	}
	if (current != NULL) free(current);
	return FALSE;
}
