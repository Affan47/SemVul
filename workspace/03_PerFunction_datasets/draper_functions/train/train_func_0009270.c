calendar_query_exec(struct ast_channel *chan, const char *cmd, char *data, char *buf, size_t len)
{
	struct ast_calendar *cal;
	struct ao2_iterator i;
	struct ast_calendar_event *event;
	struct eventlist *events;
	time_t start = INT_MIN, end = INT_MAX;
	struct ast_datastore *eventlist_datastore;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(calendar);
		AST_APP_ARG(start);
		AST_APP_ARG(end);
	);

	if (!chan) {
		ast_log(LOG_WARNING, "%s requires a channel to store the data on\n", cmd);
		return -1;
	}

	AST_STANDARD_APP_ARGS(args, data);

	if (ast_strlen_zero(args.calendar)) {
		ast_log(LOG_WARNING, "%s requires a calendar argument\n", cmd);
		return -1;
	}

	if (!(cal = find_calendar(args.calendar))) {
		ast_log(LOG_WARNING, "Unknown calendar '%s'\n", args.calendar);
		return -1;
	}

	if (!(events = ao2_alloc(sizeof(*events), eventlist_destructor))) {
		ast_log(LOG_ERROR, "Unable to allocate memory for event list\n");
		cal = unref_calendar(cal);
		return -1;
	}

	if (!ast_strlen_zero(args.start)) {
		start = atoi(args.start);
	}

	if (!ast_strlen_zero(args.end)) {
		end = atoi(args.end);
	}

	i = ao2_iterator_init(cal->events, 0);
	while ((event = ao2_iterator_next(&i))) {
		if (!(start > event->end || end < event->start)) {
			ast_debug(10, "%s (%ld - %ld) overlapped with (%ld - %ld)\n", event->summary, (long) event->start, (long) event->end, (long) start, (long) end);
			if (add_event_to_list(events, event, start, end) < 0) {
				event = ast_calendar_unref_event(event);
				cal = unref_calendar(cal);
				ao2_ref(events, -1);
				ao2_iterator_destroy(&i);
				return -1;
			}
		}

		event = ast_calendar_unref_event(event);
	}
	ao2_iterator_destroy(&i);

	ast_channel_lock(chan);
	do {
		generate_random_string(buf, len);
	} while (ast_channel_datastore_find(chan, &eventlist_datastore_info, buf));
	ast_channel_unlock(chan);

	if (!(eventlist_datastore = ast_datastore_alloc(&eventlist_datastore_info, buf))) {
		ast_log(LOG_ERROR, "Could not allocate datastore!\n");
		cal = unref_calendar(cal);
		ao2_ref(events, -1);
		return -1;
	}

	eventlist_datastore->inheritance = DATASTORE_INHERIT_FOREVER;
	eventlist_datastore->data = events;

	ast_channel_lock(chan);
	ast_channel_datastore_add(chan, eventlist_datastore);
	ast_channel_unlock(chan);

	cal = unref_calendar(cal);
	return 0;
}
