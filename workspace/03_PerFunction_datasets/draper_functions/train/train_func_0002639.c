CommentRule(List *qualname, char *comment)
{
	int			nnames;
	List	   *relname;
	char	   *rulename;
	RangeVar   *rel;
	Relation	relation;
	HeapTuple	tuple;
	Oid			reloid;
	Oid			ruleoid;


	nnames = list_length(qualname);
	if (nnames == 1)
	{

		Relation	RewriteRelation;
		HeapScanDesc scanDesc;
		ScanKeyData scanKeyData;

		rulename = strVal(linitial(qualname));


		ScanKeyInit(&scanKeyData,
					Anum_pg_rewrite_rulename,
					BTEqualStrategyNumber, F_NAMEEQ,
					PointerGetDatum(rulename));

		RewriteRelation = heap_open(RewriteRelationId, AccessShareLock);
		scanDesc = heap_beginscan(RewriteRelation, SnapshotNow,
								  1, &scanKeyData);

		tuple = heap_getnext(scanDesc, ForwardScanDirection);
		if (HeapTupleIsValid(tuple))
		{
			reloid = ((Form_pg_rewrite) GETSTRUCT(tuple))->ev_class;
			ruleoid = HeapTupleGetOid(tuple);
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("rule \"%s\" does not exist", rulename)));
			reloid = ruleoid = 0;
		}

		if (HeapTupleIsValid(tuple = heap_getnext(scanDesc,
												  ForwardScanDirection)))
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
				   errmsg("there are multiple rules named \"%s\"", rulename),
				errhint("Specify a relation name as well as a rule name.")));

		heap_endscan(scanDesc);
		heap_close(RewriteRelation, AccessShareLock);


		relation = heap_open(reloid, AccessShareLock);
	}
	else
	{

		Assert(nnames >= 2);
		relname = list_truncate(list_copy(qualname), nnames - 1);
		rulename = strVal(lfirst(list_tail(qualname)));


		rel = makeRangeVarFromNameList(relname);
		relation = heap_openrv(rel, AccessShareLock);
		reloid = RelationGetRelid(relation);


		tuple = SearchSysCache2(RULERELNAME,
								ObjectIdGetDatum(reloid),
								PointerGetDatum(rulename));
		if (!HeapTupleIsValid(tuple))
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("rule \"%s\" for relation \"%s\" does not exist",
							rulename, RelationGetRelationName(relation))));
		Assert(reloid == ((Form_pg_rewrite) GETSTRUCT(tuple))->ev_class);
		ruleoid = HeapTupleGetOid(tuple);
		ReleaseSysCache(tuple);
	}


	if (!pg_class_ownercheck(reloid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_CLASS,
					   get_rel_name(reloid));


	CreateComments(ruleoid, RewriteRelationId, 0, comment);

	heap_close(relation, NoLock);
}
