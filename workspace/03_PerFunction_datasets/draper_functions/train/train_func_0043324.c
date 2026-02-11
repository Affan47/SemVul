ExecFetchSlotTuple(TupleTableSlot *slot)
{


	Assert(slot != NULL);
	Assert(!slot->tts_isempty);


	if (TTS_HAS_PHYSICAL_TUPLE(slot))
		return slot->tts_tuple;


	return ExecMaterializeSlot(slot);
}
