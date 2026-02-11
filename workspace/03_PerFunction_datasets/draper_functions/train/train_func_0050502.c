AfterTriggerEndQuery(EState *estate)
{
	AfterTriggerEventList *events;


	Assert(afterTriggers != NULL);


	Assert(afterTriggers->query_depth >= 0);


	for (;;)
	{
		events = &afterTriggers->query_stack[afterTriggers->query_depth];
		if (afterTriggerMarkEvents(events, &afterTriggers->events, true))
		{
			CommandId	firing_id = afterTriggers->firing_counter++;


			if (afterTriggerInvokeEvents(events, firing_id, estate, true))
				break;
		}
		else
			break;
	}


	afterTriggerFreeEventList(&afterTriggers->query_stack[afterTriggers->query_depth]);

	afterTriggers->query_depth--;
}
