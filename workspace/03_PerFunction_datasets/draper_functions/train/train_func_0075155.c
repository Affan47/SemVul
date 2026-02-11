pg_foreign_data_wrapper_aclmask(Oid fdw_oid, Oid roleid,
								AclMode mask, AclMaskHow how)
{
	AclMode		result;
	HeapTuple	tuple;
	Datum		aclDatum;
	bool		isNull;
	Acl		   *acl;
	Oid			ownerId;

	Form_pg_foreign_data_wrapper fdwForm;


	if (superuser_arg(roleid))
		return mask;


	tuple = SearchSysCache1(FOREIGNDATAWRAPPEROID, ObjectIdGetDatum(fdw_oid));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errmsg("foreign-data wrapper with OID %u does not exist",
						fdw_oid)));
	fdwForm = (Form_pg_foreign_data_wrapper) GETSTRUCT(tuple);


	ownerId = fdwForm->fdwowner;

	aclDatum = SysCacheGetAttr(FOREIGNDATAWRAPPEROID, tuple,
							   Anum_pg_foreign_data_wrapper_fdwacl, &isNull);
	if (isNull)
	{

		acl = acldefault(ACL_OBJECT_FDW, ownerId);
		aclDatum = (Datum) 0;
	}
	else
	{

		acl = DatumGetAclP(aclDatum);
	}

	result = aclmask(acl, roleid, ownerId, mask, how);


	if (acl && (Pointer) acl != DatumGetPointer(aclDatum))
		pfree(acl);

	ReleaseSysCache(tuple);

	return result;
}
