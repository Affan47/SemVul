ExecStoreAllNullTuple(TupleTableSlot *slot)
{


	Assert(slot != NULL);
	Assert(slot->tts_tupleDescriptor != NULL);


	ExecClearTuple(slot);


	MemSet(slot->tts_values, 0,
		   slot->tts_tupleDescriptor->natts * sizeof(Datum));
	memset(slot->tts_isnull, true,
		   slot->tts_tupleDescriptor->natts * sizeof(bool));

	return ExecStoreVirtualTuple(slot);
}
