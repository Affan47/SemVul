ExecASUpdateTriggers(EState *estate, ResultRelInfo *relinfo)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if (trigdesc && trigdesc->trig_update_after_statement)
		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_UPDATE,
							  false, NULL, NULL, NIL,
							  GetUpdatedColumns(relinfo, estate));
}
