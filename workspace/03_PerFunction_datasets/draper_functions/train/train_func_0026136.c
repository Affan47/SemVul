ExecDelete(ItemPointer tupleid,
		   TupleTableSlot *planSlot,
		   EPQState *epqstate,
		   EState *estate)
{
	ResultRelInfo *resultRelInfo;
	Relation	resultRelationDesc;
	HTSU_Result result;
	ItemPointerData update_ctid;
	TransactionId update_xmax;


	resultRelInfo = estate->es_result_relation_info;
	resultRelationDesc = resultRelInfo->ri_RelationDesc;


	if (resultRelInfo->ri_TrigDesc &&
		resultRelInfo->ri_TrigDesc->n_before_row[TRIGGER_EVENT_DELETE] > 0)
	{
		bool		dodelete;

		dodelete = ExecBRDeleteTriggers(estate, epqstate, resultRelInfo,
										tupleid);

		if (!dodelete)
			return NULL;
	}


ldelete:;
	result = heap_delete(resultRelationDesc, tupleid,
						 &update_ctid, &update_xmax,
						 estate->es_output_cid,
						 estate->es_crosscheck_snapshot,
						 true  );
	switch (result)
	{
		case HeapTupleSelfUpdated:

			return NULL;

		case HeapTupleMayBeUpdated:
			break;

		case HeapTupleUpdated:
			if (IsXactIsoLevelSerializable)
				ereport(ERROR,
						(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
						 errmsg("could not serialize access due to concurrent update")));
			if (!ItemPointerEquals(tupleid, &update_ctid))
			{
				TupleTableSlot *epqslot;

				epqslot = EvalPlanQual(estate,
									   epqstate,
									   resultRelationDesc,
									   resultRelInfo->ri_RangeTableIndex,
									   &update_ctid,
									   update_xmax);
				if (!TupIsNull(epqslot))
				{
					*tupleid = update_ctid;
					goto ldelete;
				}
			}

			return NULL;

		default:
			elog(ERROR, "unrecognized heap_delete status: %u", result);
			return NULL;
	}

	(estate->es_processed)++;


	ExecARDeleteTriggers(estate, resultRelInfo, tupleid);


	if (resultRelInfo->ri_projectReturning)
	{


		TupleTableSlot *slot = estate->es_trig_tuple_slot;
		TupleTableSlot *rslot;
		HeapTupleData deltuple;
		Buffer		delbuffer;

		deltuple.t_self = *tupleid;
		if (!heap_fetch(resultRelationDesc, SnapshotAny,
						&deltuple, &delbuffer, false, NULL))
			elog(ERROR, "failed to fetch deleted tuple for DELETE RETURNING");

		if (slot->tts_tupleDescriptor != RelationGetDescr(resultRelationDesc))
			ExecSetSlotDescriptor(slot, RelationGetDescr(resultRelationDesc));
		ExecStoreTuple(&deltuple, slot, InvalidBuffer, false);

		rslot = ExecProcessReturning(resultRelInfo->ri_projectReturning,
									 slot, planSlot);

		ExecClearTuple(slot);
		ReleaseBuffer(delbuffer);

		return rslot;
	}

	return NULL;
}
