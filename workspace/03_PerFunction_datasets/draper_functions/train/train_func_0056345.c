ExecSetSlotDescriptor(TupleTableSlot *slot,
					  TupleDesc tupdesc)
{

	ExecClearTuple(slot);


	if (slot->tts_tupleDescriptor)
		ReleaseTupleDesc(slot->tts_tupleDescriptor);

	if (slot->tts_values)
		pfree(slot->tts_values);
	if (slot->tts_isnull)
		pfree(slot->tts_isnull);


	slot->tts_tupleDescriptor = tupdesc;
	PinTupleDesc(tupdesc);


	slot->tts_values = (Datum *)
		MemoryContextAlloc(slot->tts_mcxt, tupdesc->natts * sizeof(Datum));
	slot->tts_isnull = (bool *)
		MemoryContextAlloc(slot->tts_mcxt, tupdesc->natts * sizeof(bool));
}
