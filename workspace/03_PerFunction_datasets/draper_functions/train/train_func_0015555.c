isAnyTempNamespace(Oid namespaceId)
{
	bool		result;
	char	   *nspname;


	nspname = get_namespace_name(namespaceId);
	if (!nspname)
		return false;
	result = (strncmp(nspname, "pg_temp_", 8) == 0);
	pfree(nspname);
	return result;
}
