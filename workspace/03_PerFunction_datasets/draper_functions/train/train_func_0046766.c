ExecARUpdateTriggers(EState *estate, ResultRelInfo *relinfo,
					 ItemPointer tupleid, HeapTuple newtuple,
					 List *recheckIndexes)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if (trigdesc && trigdesc->n_after_row[TRIGGER_EVENT_UPDATE] > 0)
	{
		HeapTuple	trigtuple = GetTupleForTrigger(estate, NULL, relinfo,
												   tupleid, NULL);

		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_UPDATE,
							  true, trigtuple, newtuple, recheckIndexes,
							  GetModifiedColumns(relinfo, estate));
		heap_freetuple(trigtuple);
	}
}
