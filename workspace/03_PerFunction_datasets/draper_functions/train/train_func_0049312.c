ATExecSetTableSpace(Oid tableOid, Oid newTableSpace)
{
	Relation	rel;
	Oid			oldTableSpace;
	Oid			reltoastrelid;
	Oid			reltoastidxid;
	Oid			newrelfilenode;
	RelFileNode newrnode;
	SMgrRelation dstrel;
	Relation	pg_class;
	HeapTuple	tuple;
	Form_pg_class rd_rel;


	rel = relation_open(tableOid, AccessExclusiveLock);


	if (rel->rd_rel->relisshared || rel->rd_isnailed)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot move system relation \"%s\"",
						RelationGetRelationName(rel))));


	if (newTableSpace == GLOBALTABLESPACE_OID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("only shared relations can be placed in pg_global tablespace")));


	if (isOtherTempNamespace(RelationGetNamespace(rel)))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot move temporary tables of other sessions")));


	oldTableSpace = rel->rd_rel->reltablespace;
	if (newTableSpace == oldTableSpace ||
		(newTableSpace == MyDatabaseTableSpace && oldTableSpace == 0))
	{
		relation_close(rel, NoLock);
		return;
	}

	reltoastrelid = rel->rd_rel->reltoastrelid;
	reltoastidxid = rel->rd_rel->reltoastidxid;


	pg_class = heap_open(RelationRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy(RELOID,
							   ObjectIdGetDatum(tableOid),
							   0, 0, 0);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", tableOid);
	rd_rel = (Form_pg_class) GETSTRUCT(tuple);


	newrelfilenode = GetNewRelFileNode(newTableSpace,
									   rel->rd_rel->relisshared,
									   NULL);


	newrnode = rel->rd_node;
	newrnode.relNode = newrelfilenode;
	newrnode.spcNode = newTableSpace;

	dstrel = smgropen(newrnode);
	smgrcreate(dstrel, rel->rd_istemp, false);


	copy_relation_data(rel, dstrel);


	RelationOpenSmgr(rel);
	smgrscheduleunlink(rel->rd_smgr, rel->rd_istemp);


	smgrclose(dstrel);


	rd_rel->reltablespace = (newTableSpace == MyDatabaseTableSpace) ? InvalidOid : newTableSpace;
	rd_rel->relfilenode = newrelfilenode;
	simple_heap_update(pg_class, &tuple->t_self, tuple);
	CatalogUpdateIndexes(pg_class, tuple);

	heap_freetuple(tuple);

	heap_close(pg_class, RowExclusiveLock);

	relation_close(rel, NoLock);


	CommandCounterIncrement();


	if (OidIsValid(reltoastrelid))
		ATExecSetTableSpace(reltoastrelid, newTableSpace);
	if (OidIsValid(reltoastidxid))
		ATExecSetTableSpace(reltoastidxid, newTableSpace);
}
