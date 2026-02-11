process_machine_id_event(auparse_state_t *au)
{
	uid_t uid;
	time_t time;
	const char *seclevel, *uuid, *name;
	struct event *event;
	int success;

	seclevel = get_seclevel(auparse_find_field(au, "vm-ctx"));
	if (seclevel == NULL) {
		if (debug)
			fprintf(stderr, "Security context not found for "
					"MACHINE_ID event.\n");
	}

	if (extract_virt_fields(au, &uuid, &uid, &time, &name, &success))
		return 0;

	event = event_alloc();
	if (event == NULL)
		return 1;
	event->type = ET_MACHINE_ID;
	event->uuid = copy_str(uuid);
	event->name = copy_str(name);
	event->success = success;
	event->seclevel = copy_str(seclevel);
	event->uid = uid;
	event->start = time;
	add_proof(event, au);
	if (list_append(events, event) == NULL) {
		event_free(event);
		return 1;
	}
	return 0;
}
