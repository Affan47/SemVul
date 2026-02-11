AfterTriggerPendingOnRel(Oid relid)
{
	AfterTriggerEvent event;
	AfterTriggerEventChunk *chunk;
	int			depth;


	if (afterTriggers == NULL)
		return false;


	for_each_event_chunk(event, chunk, afterTriggers->events)
	{
		AfterTriggerShared evtshared = GetTriggerSharedData(event);


		if (event->ate_flags & AFTER_TRIGGER_DONE)
			continue;

		if (evtshared->ats_relid == relid)
			return true;
	}


	for (depth = 0; depth <= afterTriggers->query_depth; depth++)
	{
		for_each_event_chunk(event, chunk, afterTriggers->query_stack[depth])
		{
			AfterTriggerShared evtshared = GetTriggerSharedData(event);

			if (event->ate_flags & AFTER_TRIGGER_DONE)
				continue;

			if (evtshared->ats_relid == relid)
				return true;
		}
	}

	return false;
}
