AfterTriggerFireDeferred(void)
{
	AfterTriggerEventList *events;


	Assert(afterTriggers != NULL);


	Assert(afterTriggers->query_depth == -1);


	events = &afterTriggers->events;
	if (events->head != NULL)
		ActiveSnapshot = CopySnapshot(GetTransactionSnapshot());


	while (afterTriggerMarkEvents(events, NULL, false))
	{
		CommandId	firing_id = afterTriggers->firing_counter++;

		afterTriggerInvokeEvents(-1, firing_id, NULL, true);
	}

	Assert(events->head == NULL);
}
