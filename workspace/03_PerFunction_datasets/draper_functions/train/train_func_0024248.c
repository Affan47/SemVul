eventCleanup(void)
{
    struct ev_entry **p = &tasks;

    debug(41, 2) ("eventCleanup\n");

    while (*p) {
	struct ev_entry *event = *p;
	if (!cbdataValid(event->arg)) {
	    debug(41, 2) ("eventCleanup: cleaning '%s'\n", event->name);
	    *p = event->next;
	    cbdataUnlock(event->arg);
	    memFree(event, MEM_EVENT);
	} else {
	    p = &event->next;
	}
    }
}
