ExecARInsertTriggers(EState *estate, ResultRelInfo *relinfo,
					 HeapTuple trigtuple, List *recheckIndexes)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if (trigdesc && trigdesc->trig_insert_after_row)
		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_INSERT,
							  true, NULL, trigtuple, recheckIndexes, NULL);
}
