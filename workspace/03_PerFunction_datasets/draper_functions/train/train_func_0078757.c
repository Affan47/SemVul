apmd_log_event(apm_event_t event, char *msg)
{
	int i;

	for (i=0; i<NUM_ACTIONS; i++) {
		if (actions[i].event == event)
			break;
	}

	if (i == NUM_ACTIONS)
		return;

	if (actions[i].log) {
		APMD_SYSLOG(LOG_INFO, "%s", msg);
	}

	return;
}
