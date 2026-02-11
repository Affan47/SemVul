gen_alloc(struct ast_channel *chan, void *params)
{
	struct ivr_localuser *u = params;
	struct gen_state *state;

	if (!(state = ast_calloc(1, sizeof(*state))))
		return NULL;

	state->u = u;

	return state;
}
