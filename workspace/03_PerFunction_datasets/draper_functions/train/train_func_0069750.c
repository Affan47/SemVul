process_message(struct mansession *s, struct message *m)
{
	int x;
	char event[80];
	strncpy(event, get_header(m, "Event"), sizeof(event));
	if (!strlen(event)) {
		fprintf(stderr, "Missing event in request\n");
		return 0;
	}
	for (x=0;x<sizeof(events) / sizeof(events[0]);x++) {
		if (!strcasecmp(event, events[x].event)) {
			if (events[x].func(s, m))
				return -1;
			break;
		}
	}
	if (x >= sizeof(events) / sizeof(events[0]))
		fprintf(stderr, "Ignoring unknown event '%s'\n", event);
#if 0
	for (x=0;x<m->hdrcount;x++) {
		printf("Header: %s\n", m->headers[x]);
	}
#endif
	return 0;
}
