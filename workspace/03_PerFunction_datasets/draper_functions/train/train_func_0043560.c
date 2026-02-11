RelationBuildDesc(Oid targetRelId, bool insertIt)
{
	Relation	relation;
	Oid			relid;
	HeapTuple	pg_class_tuple;
	Form_pg_class relp;


	pg_class_tuple = ScanPgRelation(targetRelId, true);


	if (!HeapTupleIsValid(pg_class_tuple))
		return NULL;


	relid = HeapTupleGetOid(pg_class_tuple);
	relp = (Form_pg_class) GETSTRUCT(pg_class_tuple);


	relation = AllocateRelationDesc(relp);


	RelationGetRelid(relation) = relid;


	relation->rd_refcnt = 0;
	relation->rd_isnailed = false;
	relation->rd_createSubid = InvalidSubTransactionId;
	relation->rd_newRelfilenodeSubid = InvalidSubTransactionId;
	relation->rd_istemp = isTempOrToastNamespace(relation->rd_rel->relnamespace);


	RelationBuildTupleDesc(relation);


	if (relation->rd_rel->relhasrules)
		RelationBuildRuleLock(relation);
	else
	{
		relation->rd_rules = NULL;
		relation->rd_rulescxt = NULL;
	}

	if (relation->rd_rel->reltriggers > 0)
		RelationBuildTriggers(relation);
	else
		relation->trigdesc = NULL;


	if (OidIsValid(relation->rd_rel->relam))
		RelationInitIndexAccessInfo(relation);


	RelationParseRelOptions(relation, pg_class_tuple);


	RelationInitLockInfo(relation);


	RelationInitPhysicalAddr(relation);


	relation->rd_smgr = NULL;


	heap_freetuple(pg_class_tuple);


	if (insertIt)
		RelationCacheInsert(relation);


	relation->rd_isvalid = true;

	return relation;
}
