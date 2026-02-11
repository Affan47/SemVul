reindex_index(Oid indexId, bool skip_constraint_checks)
{
	Relation	iRel,
				heapRelation,
				pg_index;
	Oid			heapId;
	IndexInfo  *indexInfo;
	HeapTuple	indexTuple;
	Form_pg_index indexForm;
	volatile bool skipped_constraint = false;


	heapId = IndexGetRelation(indexId);
	heapRelation = heap_open(heapId, ShareLock);


	iRel = index_open(indexId, AccessExclusiveLock);


	if (RELATION_IS_OTHER_TEMP(iRel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
			   errmsg("cannot reindex temporary tables of other sessions")));


	CheckTableNotInUse(iRel, "REINDEX INDEX");

	PG_TRY();
	{

		SetReindexProcessing(heapId, indexId);


		indexInfo = BuildIndexInfo(iRel);


		if (skip_constraint_checks)
		{
			if (indexInfo->ii_Unique || indexInfo->ii_ExclusionOps != NULL)
				skipped_constraint = true;
			indexInfo->ii_Unique = false;
			indexInfo->ii_ExclusionOps = NULL;
			indexInfo->ii_ExclusionProcs = NULL;
			indexInfo->ii_ExclusionStrats = NULL;
		}


		RelationSetNewRelfilenode(iRel, InvalidTransactionId);


		index_build(heapRelation, iRel, indexInfo, false);
	}
	PG_CATCH();
	{

		ResetReindexProcessing();
		PG_RE_THROW();
	}
	PG_END_TRY();
	ResetReindexProcessing();


	if (!skipped_constraint)
	{
		pg_index = heap_open(IndexRelationId, RowExclusiveLock);

		indexTuple = SearchSysCacheCopy1(INDEXRELID,
										 ObjectIdGetDatum(indexId));
		if (!HeapTupleIsValid(indexTuple))
			elog(ERROR, "cache lookup failed for index %u", indexId);
		indexForm = (Form_pg_index) GETSTRUCT(indexTuple);

		if (!indexForm->indisvalid || !indexForm->indisready ||
			(indexForm->indcheckxmin && !indexInfo->ii_BrokenHotChain))
		{
			indexForm->indisvalid = true;
			indexForm->indisready = true;
			if (!indexInfo->ii_BrokenHotChain)
				indexForm->indcheckxmin = false;
			simple_heap_update(pg_index, &indexTuple->t_self, indexTuple);
			CatalogUpdateIndexes(pg_index, indexTuple);
		}

		heap_close(pg_index, RowExclusiveLock);
	}


	index_close(iRel, NoLock);
	heap_close(heapRelation, NoLock);
}
