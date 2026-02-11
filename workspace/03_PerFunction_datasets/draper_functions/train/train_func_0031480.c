presence_state_cb(const struct ast_event *event, void *unused)
{
	struct presencechange *pc;
	const char *tmp;

	if (!(pc = ao2_alloc(sizeof(*pc), presencechange_destroy))) {
		return;
	}

	tmp = ast_event_get_ie_str(event, AST_EVENT_IE_PRESENCE_PROVIDER);
	if (ast_strlen_zero(tmp)) {
		ast_log(LOG_ERROR, "Received invalid event that had no presence provider IE\n");
		ao2_ref(pc, -1);
		return;
	}
	pc->provider = ast_strdup(tmp);

	pc->state = ast_event_get_ie_uint(event, AST_EVENT_IE_PRESENCE_STATE);
	if (pc->state < 0) {
		ao2_ref(pc, -1);
		return;
	}

	if ((tmp = ast_event_get_ie_str(event, AST_EVENT_IE_PRESENCE_SUBTYPE))) {
		pc->subtype = ast_strdup(tmp);
	}

	if ((tmp = ast_event_get_ie_str(event, AST_EVENT_IE_PRESENCE_MESSAGE))) {
		pc->message = ast_strdup(tmp);
	}


	if (ast_taskprocessor_push(extension_state_tps, handle_presencechange, pc) < 0) {
		ao2_ref(pc, -1);
	}
}
