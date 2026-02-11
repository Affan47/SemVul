CreateUserMapping(CreateUserMappingStmt *stmt)
{
	Relation	rel;
	Datum		useoptions;
	Datum		values[Natts_pg_user_mapping];
	bool		nulls[Natts_pg_user_mapping];
	HeapTuple	tuple;
	Oid			useId;
	Oid			umId;
	ObjectAddress myself;
	ObjectAddress referenced;
	ForeignServer *srv;
	ForeignDataWrapper *fdw;

	useId = GetUserOidFromMapping(stmt->username, false);


	srv = GetForeignServerByName(stmt->servername, false);

	user_mapping_ddl_aclcheck(useId, srv->serverid, stmt->servername);


	umId = GetSysCacheOid2(USERMAPPINGUSERSERVER,
						   ObjectIdGetDatum(useId),
						   ObjectIdGetDatum(srv->serverid));
	if (OidIsValid(umId))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("user mapping \"%s\" already exists for server %s",
						MappingUserName(useId),
						stmt->servername)));

	fdw = GetForeignDataWrapper(srv->fdwid);


	rel = heap_open(UserMappingRelationId, RowExclusiveLock);

	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	values[Anum_pg_user_mapping_umuser - 1] = ObjectIdGetDatum(useId);
	values[Anum_pg_user_mapping_umserver - 1] = ObjectIdGetDatum(srv->serverid);


	useoptions = transformGenericOptions(UserMappingRelationId,
										 PointerGetDatum(NULL),
										 stmt->options,
										 fdw->fdwvalidator);

	if (PointerIsValid(DatumGetPointer(useoptions)))
		values[Anum_pg_user_mapping_umoptions - 1] = useoptions;
	else
		nulls[Anum_pg_user_mapping_umoptions - 1] = true;

	tuple = heap_form_tuple(rel->rd_att, values, nulls);

	umId = simple_heap_insert(rel, tuple);

	CatalogUpdateIndexes(rel, tuple);

	heap_freetuple(tuple);


	myself.classId = UserMappingRelationId;
	myself.objectId = umId;
	myself.objectSubId = 0;

	referenced.classId = ForeignServerRelationId;
	referenced.objectId = srv->serverid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	if (OidIsValid(useId))

		recordDependencyOnOwner(UserMappingRelationId, umId, useId);


	InvokeObjectAccessHook(OAT_POST_CREATE, UserMappingRelationId, umId, 0);

	heap_close(rel, NoLock);
}
