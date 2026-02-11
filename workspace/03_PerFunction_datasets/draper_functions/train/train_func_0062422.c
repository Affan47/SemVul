gfxr_get_cursor(gfx_resstate_t *state, int nr)
{
	gfx_resource_type_t restype = GFX_RESOURCE_TYPE_CURSOR;
	sbtree_t *tree = state->resource_trees[restype];
	gfx_resource_t *res = NULL;
	int hash = gfxr_interpreter_options_hash(restype, state->version,
						 state->options, state->misc_payload, 0);

	if (!tree)
		return NULL;

	res = (gfx_resource_t *) sbtree_get(tree, nr);

	if (!res || res->mode != hash) {
		gfx_pixmap_t *cursor = gfxr_interpreter_get_cursor(state, nr,
								   state->misc_payload);

		if (!cursor)
			return NULL;

		if (!res) {
			res = (gfx_resource_t*)sci_malloc(sizeof(gfx_resource_t));
			res->scaled_data.pointer = NULL;
			res->ID = GFXR_RES_ID(restype, nr);
			res->lock_sequence_nr = state->tag_lock_counter;
			res->mode = hash;
			sbtree_set(tree, nr, (void *) res);
		} else {
			gfx_free_pixmap(state->driver, res->unscaled_data.pointer);
		}
		gfx_get_res_config(state->options, cursor);
		gfx_xlate_pixmap(cursor, state->driver->mode, state->options->cursor_xlate_filter);
                gfxr_endianness_adjust(cursor, state->driver->mode);

		res->unscaled_data.pointer = cursor;

		return cursor;
	} else {
		res->lock_sequence_nr = state->tag_lock_counter;
		return res->unscaled_data.pointer;
	}
}
