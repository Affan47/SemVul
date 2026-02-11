cluster(ClusterStmt *stmt, bool isTopLevel)
{
	if (stmt->relation != NULL)
	{

		Oid			tableOid,
					indexOid = InvalidOid;
		Relation	rel;
		RelToCluster rvtc;


		rel = heap_openrv(stmt->relation, AccessExclusiveLock);

		tableOid = RelationGetRelid(rel);


		if (!pg_class_ownercheck(tableOid, GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_CLASS,
						   RelationGetRelationName(rel));


		if (RELATION_IS_OTHER_TEMP(rel))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
			   errmsg("cannot cluster temporary tables of other sessions")));

		if (stmt->indexname == NULL)
		{
			ListCell   *index;


			foreach(index, RelationGetIndexList(rel))
			{
				HeapTuple	idxtuple;
				Form_pg_index indexForm;

				indexOid = lfirst_oid(index);
				idxtuple = SearchSysCache(INDEXRELID,
										  ObjectIdGetDatum(indexOid),
										  0, 0, 0);
				if (!HeapTupleIsValid(idxtuple))
					elog(ERROR, "cache lookup failed for index %u", indexOid);
				indexForm = (Form_pg_index) GETSTRUCT(idxtuple);
				if (indexForm->indisclustered)
				{
					ReleaseSysCache(idxtuple);
					break;
				}
				ReleaseSysCache(idxtuple);
				indexOid = InvalidOid;
			}

			if (!OidIsValid(indexOid))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("there is no previously clustered index for table \"%s\"",
								stmt->relation->relname)));
		}
		else
		{


			indexOid = get_relname_relid(stmt->indexname,
										 rel->rd_rel->relnamespace);
			if (!OidIsValid(indexOid))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
					   errmsg("index \"%s\" for table \"%s\" does not exist",
							  stmt->indexname, stmt->relation->relname)));
		}


		rvtc.tableOid = tableOid;
		rvtc.indexOid = indexOid;


		heap_close(rel, NoLock);


		cluster_rel(&rvtc, false, stmt->verbose);
	}
	else
	{


		MemoryContext cluster_context;
		List	   *rvs;
		ListCell   *rv;


		PreventTransactionChain(isTopLevel, "CLUSTER");


		cluster_context = AllocSetContextCreate(PortalContext,
												"Cluster",
												ALLOCSET_DEFAULT_MINSIZE,
												ALLOCSET_DEFAULT_INITSIZE,
												ALLOCSET_DEFAULT_MAXSIZE);


		rvs = get_tables_to_cluster(cluster_context);


		PopActiveSnapshot();
		CommitTransactionCommand();


		foreach(rv, rvs)
		{
			RelToCluster *rvtc = (RelToCluster *) lfirst(rv);


			StartTransactionCommand();

			PushActiveSnapshot(GetTransactionSnapshot());
			cluster_rel(rvtc, true, stmt->verbose);
			PopActiveSnapshot();
			CommitTransactionCommand();
		}


		StartTransactionCommand();


		MemoryContextDelete(cluster_context);
	}
}
