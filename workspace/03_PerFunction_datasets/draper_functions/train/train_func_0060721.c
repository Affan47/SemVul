CommentConstraint(List *qualname, char *comment)
{
	int			nnames;
	List	   *relName;
	char	   *conName;
	RangeVar   *rel;
	Relation	relation;
	Oid			conOid;


	nnames = list_length(qualname);
	if (nnames < 2)
		elog(ERROR, "must specify relation and constraint");
	relName = list_truncate(list_copy(qualname), nnames - 1);
	conName = strVal(lfirst(list_tail(qualname)));


	rel = makeRangeVarFromNameList(relName);
	relation = heap_openrv(rel, AccessShareLock);


	if (!pg_class_ownercheck(RelationGetRelid(relation), GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_CLASS,
					   RelationGetRelationName(relation));

	conOid = GetConstraintByName(RelationGetRelid(relation), conName);


	CreateComments(conOid, ConstraintRelationId, 0, comment);


	heap_close(relation, NoLock);
}
