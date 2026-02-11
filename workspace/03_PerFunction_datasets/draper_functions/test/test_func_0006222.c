InsertTrigger(TriggerDesc *trigdesc, Trigger *trigger, int indx)
{
	uint16	   *n;
	int		  **t,
			  **tp;

	if (TRIGGER_FOR_ROW(trigger->tgtype))
	{

		if (TRIGGER_FOR_BEFORE(trigger->tgtype))
		{
			n = trigdesc->n_before_row;
			t = trigdesc->tg_before_row;
		}
		else
		{
			n = trigdesc->n_after_row;
			t = trigdesc->tg_after_row;
		}
	}
	else
	{

		if (TRIGGER_FOR_BEFORE(trigger->tgtype))
		{
			n = trigdesc->n_before_statement;
			t = trigdesc->tg_before_statement;
		}
		else
		{
			n = trigdesc->n_after_statement;
			t = trigdesc->tg_after_statement;
		}
	}

	if (TRIGGER_FOR_INSERT(trigger->tgtype))
	{
		tp = &(t[TRIGGER_EVENT_INSERT]);
		if (*tp == NULL)
			*tp = (int *) palloc(trigdesc->numtriggers * sizeof(int));
		(*tp)[n[TRIGGER_EVENT_INSERT]] = indx;
		(n[TRIGGER_EVENT_INSERT])++;
	}

	if (TRIGGER_FOR_DELETE(trigger->tgtype))
	{
		tp = &(t[TRIGGER_EVENT_DELETE]);
		if (*tp == NULL)
			*tp = (int *) palloc(trigdesc->numtriggers * sizeof(int));
		(*tp)[n[TRIGGER_EVENT_DELETE]] = indx;
		(n[TRIGGER_EVENT_DELETE])++;
	}

	if (TRIGGER_FOR_UPDATE(trigger->tgtype))
	{
		tp = &(t[TRIGGER_EVENT_UPDATE]);
		if (*tp == NULL)
			*tp = (int *) palloc(trigdesc->numtriggers * sizeof(int));
		(*tp)[n[TRIGGER_EVENT_UPDATE]] = indx;
		(n[TRIGGER_EVENT_UPDATE])++;
	}
}
