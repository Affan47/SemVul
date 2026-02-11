heap_drop_with_catalog(Oid relid)
{
	Relation	rel;


	rel = relation_open(relid, AccessExclusiveLock);


	if (rel->rd_rel->relkind != RELKIND_VIEW &&
		rel->rd_rel->relkind != RELKIND_COMPOSITE_TYPE)
	{
		RelationOpenSmgr(rel);
		smgrscheduleunlink(rel->rd_smgr, rel->rd_istemp);
	}


	relation_close(rel, NoLock);


	remove_on_commit_action(relid);


	RelationForgetRelation(relid);


	RelationRemoveInheritance(relid);


	RemoveStatistics(relid, 0);


	DeleteAttributeTuples(relid);


	DeleteRelationTuple(relid);
}
