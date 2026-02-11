gn_calnote_fill(gn_calnote *note, char *type, char *text, char *meeting_location,
		    char *desc, char *time, char *endtime, char *alarm)
{
	dprintf("Start time (YYYY-MM-DD HH:MM:SS):\n");
	vcal_time_get(&note->time, time);
	dprintf("End time (YYYY-MM-DD HH:MM:SS):\n");
	vcal_time_get(&note->end_time, endtime);
	dprintf("Alarm time (YYYY-MM-DD HH:MM:SS):\n");
	vcal_time_get(&note->alarm.timestamp, alarm);
	if (note->alarm.timestamp.year) {
		note->alarm.enabled = 1;
		note->alarm.tone = alarmtone;
	}

	snprintf(note->text, 256, "%s", text);
	note->phone_number[0] = 0;
	dprintf("Text: %s\n", note->text);


	if (!strcmp(type, "PHONE CALL")) {
		snprintf(note->phone_number, 48, "%s", text);
		dprintf("Phone: %s\n", note->phone_number);
		if (desc[0] != 0) {
			snprintf(note->text, 256, "%s", desc);
			dprintf("Desc: %s\n", note->text);
		}
		note->type = GN_CALNOTE_CALL;
	} else if (!strcmp(type, "MEETING")) {
		note->type = GN_CALNOTE_MEETING;
		if (meeting_location[0] != 0) {
			snprintf(note->mlocation, 64, "%s", meeting_location);
			dprintf("Location: %s\n", note->mlocation);
		}
	} else if (!strcmp(type, "SPECIAL OCCASION"))
		note->type = GN_CALNOTE_BIRTHDAY;
	else if (!strcmp(type, "REMINDER"))
		note->type = GN_CALNOTE_REMINDER;
	else
		note->type = GN_CALNOTE_MEMO;

	return 0;
}
