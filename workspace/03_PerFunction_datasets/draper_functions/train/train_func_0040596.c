playtones_release(struct ast_channel *chan, void *params)
{
	struct playtones_state *ps = params;

	if (chan) {
		ast_set_write_format(chan, &ps->origwfmt);
	}

	if (ps->items) {
		ast_free(ps->items);
		ps->items = NULL;
	}

	ast_free(ps);
}
