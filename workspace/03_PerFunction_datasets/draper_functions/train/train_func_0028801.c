smgrin(PG_FUNCTION_ARGS)
{
	char	   *s = PG_GETARG_CSTRING(0);
	int16		i;

	for (i = 0; i < NStorageManagers; i++)
	{
		if (strcmp(s, StorageManager[i].smgr_name) == 0)
			PG_RETURN_INT16(i);
	}
	elog(ERROR, "unrecognized storage manager name \"%s\"", s);
	PG_RETURN_INT16(0);
}
