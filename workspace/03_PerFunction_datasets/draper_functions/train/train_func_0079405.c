ExecBRInsertTriggers(EState *estate, ResultRelInfo *relinfo,
					 TupleTableSlot *slot)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	HeapTuple	slottuple = ExecMaterializeSlot(slot);
	HeapTuple	newtuple = slottuple;
	HeapTuple	oldtuple;
	TriggerData LocTriggerData;
	int			i;

	LocTriggerData.type = T_TriggerData;
	LocTriggerData.tg_event = TRIGGER_EVENT_INSERT |
		TRIGGER_EVENT_ROW |
		TRIGGER_EVENT_BEFORE;
	LocTriggerData.tg_relation = relinfo->ri_RelationDesc;
	LocTriggerData.tg_newtuple = NULL;
	LocTriggerData.tg_newtuplebuf = InvalidBuffer;
	for (i = 0; i < trigdesc->numtriggers; i++)
	{
		Trigger    *trigger = &trigdesc->triggers[i];

		if (!TRIGGER_TYPE_MATCHES(trigger->tgtype,
								  TRIGGER_TYPE_ROW,
								  TRIGGER_TYPE_BEFORE,
								  TRIGGER_TYPE_INSERT))
			continue;
		if (!TriggerEnabled(estate, relinfo, trigger, LocTriggerData.tg_event,
							NULL, NULL, newtuple))
			continue;

		LocTriggerData.tg_trigtuple = oldtuple = newtuple;
		LocTriggerData.tg_trigtuplebuf = InvalidBuffer;
		LocTriggerData.tg_trigger = trigger;
		newtuple = ExecCallTriggerFunc(&LocTriggerData,
									   i,
									   relinfo->ri_TrigFunctions,
									   relinfo->ri_TrigInstrument,
									   GetPerTupleMemoryContext(estate));
		if (oldtuple != newtuple && oldtuple != slottuple)
			heap_freetuple(oldtuple);
		if (newtuple == NULL)
			return NULL;
	}

	if (newtuple != slottuple)
	{


		TupleTableSlot *newslot = estate->es_trig_tuple_slot;
		TupleDesc	tupdesc = RelationGetDescr(relinfo->ri_RelationDesc);

		if (newslot->tts_tupleDescriptor != tupdesc)
			ExecSetSlotDescriptor(newslot, tupdesc);
		ExecStoreTuple(newtuple, newslot, InvalidBuffer, false);
		slot = newslot;
	}
	return slot;
}
