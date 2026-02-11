GetDefaultTablespace(bool forTemp)
{
	Oid			result;


	if (forTemp)
	{
		PrepareTempTablespaces();
		return GetNextTempTableSpace();
	}


	if (default_tablespace == NULL || default_tablespace[0] == '\0')
		return InvalidOid;


	result = get_tablespace_oid(default_tablespace);


	if (result == MyDatabaseTableSpace)
		result = InvalidOid;
	return result;
}
