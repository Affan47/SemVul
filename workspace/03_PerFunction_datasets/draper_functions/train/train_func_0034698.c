ExecASDeleteTriggers(EState *estate, ResultRelInfo *relinfo)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if (trigdesc && trigdesc->trig_delete_after_statement)
		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_DELETE,
							  false, NULL, NULL, NIL, NULL);
}
