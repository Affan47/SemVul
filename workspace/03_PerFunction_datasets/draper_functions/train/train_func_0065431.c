audiohook_inheritance_fixup(void *data, struct ast_channel *old_chan, struct ast_channel *new_chan)
{
	struct inheritable_audiohook *audiohook = NULL;
	struct audiohook_inheritance_datastore *datastore = data;

	ast_debug(2, "inheritance fixup occurring for channels %s(%p) and %s(%p)", ast_channel_name(old_chan), old_chan, ast_channel_name(new_chan), new_chan);

	AST_LIST_TRAVERSE(&datastore->allowed_list, audiohook, list) {
		ast_audiohook_move_by_source(old_chan, new_chan, audiohook->source);
		ast_debug(3, "Moved audiohook %s from %s(%p) to %s(%p)\n",
			audiohook->source, ast_channel_name(old_chan), old_chan, ast_channel_name(new_chan), new_chan);
	}
	return;
}
