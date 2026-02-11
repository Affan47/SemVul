action_alloc(Text *txt) {
	Action *old, *new = calloc(1, sizeof(Action));
	if (!new)
		return NULL;
	new->time = time(NULL);

	while ((old = action_pop(&txt->redo)))
		action_free(old);
	txt->current_action = new;
	action_push(&txt->undo, new);
	return new;
}
