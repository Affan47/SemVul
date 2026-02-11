GetTupleForTrigger(EState *estate,
				   EPQState *epqstate,
				   ResultRelInfo *relinfo,
				   ItemPointer tid,
				   TupleTableSlot **newSlot)
{
	Relation	relation = relinfo->ri_RelationDesc;
	HeapTupleData tuple;
	HeapTuple	result;
	Buffer		buffer;

	if (newSlot != NULL)
	{
		HTSU_Result test;
		ItemPointerData update_ctid;
		TransactionId update_xmax;

		*newSlot = NULL;


		Assert(epqstate != NULL);


ltrmark:;
		tuple.t_self = *tid;
		test = heap_lock_tuple(relation, &tuple, &buffer,
							   &update_ctid, &update_xmax,
							   estate->es_output_cid,
							   LockTupleExclusive, false);
		switch (test)
		{
			case HeapTupleSelfUpdated:

				ReleaseBuffer(buffer);
				return NULL;

			case HeapTupleMayBeUpdated:
				break;

			case HeapTupleUpdated:
				ReleaseBuffer(buffer);
				if (IsolationUsesXactSnapshot())
					ereport(ERROR,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("could not serialize access due to concurrent update")));
				if (!ItemPointerEquals(&update_ctid, &tuple.t_self))
				{

					TupleTableSlot *epqslot;

					epqslot = EvalPlanQual(estate,
										   epqstate,
										   relation,
										   relinfo->ri_RangeTableIndex,
										   &update_ctid,
										   update_xmax);
					if (!TupIsNull(epqslot))
					{
						*tid = update_ctid;
						*newSlot = epqslot;


						goto ltrmark;
					}
				}


				return NULL;

			default:
				ReleaseBuffer(buffer);
				elog(ERROR, "unrecognized heap_lock_tuple status: %u", test);
				return NULL;
		}
	}
	else
	{
		Page		page;
		ItemId		lp;

		buffer = ReadBuffer(relation, ItemPointerGetBlockNumber(tid));

		page = BufferGetPage(buffer);
		lp = PageGetItemId(page, ItemPointerGetOffsetNumber(tid));

		Assert(ItemIdIsNormal(lp));

		tuple.t_data = (HeapTupleHeader) PageGetItem(page, lp);
		tuple.t_len = ItemIdGetLength(lp);
		tuple.t_self = *tid;
		tuple.t_tableOid = RelationGetRelid(relation);
	}

	result = heap_copytuple(&tuple);
	ReleaseBuffer(buffer);

	return result;
}
