_fluid_seq_queue_pre_insert(fluid_sequencer_t* seq, fluid_event_t * evt)
{
	fluid_evt_entry * evtentry = _fluid_seq_heap_get_free(seq->heap);
	if (evtentry == NULL) {

		fluid_log(FLUID_PANIC, "sequencer: no more free events\n");
		return -1;
	}

	evtentry->next = NULL;
	evtentry->entryType = FLUID_EVT_ENTRY_INSERT;
	FLUID_MEMCPY(&(evtentry->evt), evt, sizeof(fluid_event_t));

	fluid_mutex_lock(seq->mutex);


	if (seq->preQueueLast) {
		seq->preQueueLast->next = evtentry;
	} else {
		seq->preQueue = evtentry;
	}
	seq->preQueueLast = evtentry;

	fluid_mutex_unlock(seq->mutex);

	return (0);
}
