pg_ts_dict_ownercheck(Oid dict_oid, Oid roleid)
{
	HeapTuple	tuple;
	Oid			ownerId;


	if (superuser_arg(roleid))
		return true;

	tuple = SearchSysCache1(TSDICTOID, ObjectIdGetDatum(dict_oid));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("text search dictionary with OID %u does not exist",
						dict_oid)));

	ownerId = ((Form_pg_ts_dict) GETSTRUCT(tuple))->dictowner;

	ReleaseSysCache(tuple);

	return has_privs_of_role(roleid, ownerId);
}
