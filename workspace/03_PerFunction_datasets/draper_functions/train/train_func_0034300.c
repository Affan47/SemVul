EventTriggerDDLCommandStart(Node *parsetree)
{
	List	   *runlist;
	EventTriggerData trigdata;


	if (!IsUnderPostmaster)
		return;

	runlist = EventTriggerCommonSetup(parsetree,
									  EVT_DDLCommandStart,
									  "ddl_command_start",
									  &trigdata);
	if (runlist == NIL)
		return;


	EventTriggerInvoke(runlist, &trigdata);


	list_free(runlist);


	CommandCounterIncrement();
}
