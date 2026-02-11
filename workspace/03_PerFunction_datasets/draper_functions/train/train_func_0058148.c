cm_notify_start(struct cm_store_entry *entry, enum cm_notify_event event)
{
	struct cm_notify_state *state;
	struct cm_notify_details details;
	state = talloc_ptrtype(entry, state);
	if (state != NULL) {
		memset(&details, 0, sizeof(details));
		details.event = event;
		state->subproc = cm_subproc_start(cm_notify_main,
						  NULL, entry, &details);
		if (state->subproc == NULL) {
			talloc_free(state);
			state = NULL;
		}
	}
	return state;
}
