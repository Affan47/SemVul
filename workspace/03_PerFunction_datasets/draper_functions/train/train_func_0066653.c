heap_create(const char *relname,
			Oid relnamespace,
			Oid reltablespace,
			Oid relid,
			TupleDesc tupDesc,
			char relkind,
			bool shared_relation,
			bool allow_system_table_mods)
{
	bool		create_storage;
	Relation	rel;


	Assert(OidIsValid(relid));


	if (!allow_system_table_mods &&
		(IsSystemNamespace(relnamespace) || IsToastNamespace(relnamespace)) &&
		IsNormalProcessingMode())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to create \"%s.%s\"",
						get_namespace_name(relnamespace), relname),
		errdetail("System catalog modifications are currently disallowed.")));


	switch (relkind)
	{
		case RELKIND_VIEW:
		case RELKIND_COMPOSITE_TYPE:
			create_storage = false;


			reltablespace = InvalidOid;
			break;
		case RELKIND_SEQUENCE:
			create_storage = true;


			reltablespace = InvalidOid;
			break;
		default:
			create_storage = true;
			break;
	}


	if (reltablespace == MyDatabaseTableSpace)
		reltablespace = InvalidOid;


	rel = RelationBuildLocalRelation(relname,
									 relnamespace,
									 tupDesc,
									 relid,
									 reltablespace,
									 shared_relation);


	if (create_storage)
	{
		RelationOpenSmgr(rel);
		RelationCreateStorage(rel->rd_node, rel->rd_istemp);
	}

	return rel;
}
