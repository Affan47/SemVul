timer_add (int ref, float timeout, int repeat, char *command)
{
	timer *tim;
	GSList *list;

	if (ref == 0)
	{
		ref = 1;
		list = timer_list;
		while (list)
		{
			tim = list->data;
			if (tim->ref >= ref)
				ref = tim->ref + 1;
			list = list->next;
		}
	}

	tim = malloc (sizeof (timer));
	tim->ref = ref;
	tim->repeat = repeat;
	tim->timeout = timeout;
	tim->command = strdup (command);
	tim->context = hexchat_get_context (ph);
	tim->forever = FALSE;

	if (repeat == 0)
		tim->forever = TRUE;

	tim->hook = hexchat_hook_timer (ph, timeout * 1000.0, (void *)timeout_cb, tim);
	timer_list = g_slist_append (timer_list, tim);
}
