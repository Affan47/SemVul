local_write(struct ast_channel *chan, const char *cmd, char *var, const char *value)
{
	struct ast_datastore *stack_store;
	struct gosub_stack_list *oldlist;
	struct gosub_stack_frame *frame;

	ast_channel_lock(chan);
	if (!(stack_store = ast_channel_datastore_find(chan, &stack_info, NULL))) {
		ast_log(LOG_ERROR, "Tried to set LOCAL(%s), but we aren't within a Gosub routine\n", var);
		ast_channel_unlock(chan);
		return -1;
	}

	oldlist = stack_store->data;
	AST_LIST_LOCK(oldlist);
	frame = AST_LIST_FIRST(oldlist);

	if (frame) {
		frame_set_var(chan, frame, var, value);
	}

	AST_LIST_UNLOCK(oldlist);
	ast_channel_unlock(chan);

	return 0;
}
