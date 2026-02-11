ExecClearTuple(TupleTableSlot *slot)
{


	Assert(slot != NULL);


	if (slot->tts_shouldFree)
		heap_freetuple(slot->tts_tuple);
	if (slot->tts_shouldFreeMin)
		heap_free_minimal_tuple(slot->tts_mintuple);

	slot->tts_tuple = NULL;
	slot->tts_mintuple = NULL;
	slot->tts_shouldFree = false;
	slot->tts_shouldFreeMin = false;


	if (BufferIsValid(slot->tts_buffer))
		ReleaseBuffer(slot->tts_buffer);

	slot->tts_buffer = InvalidBuffer;


	slot->tts_isempty = true;
	slot->tts_nvalid = 0;

	return slot;
}
