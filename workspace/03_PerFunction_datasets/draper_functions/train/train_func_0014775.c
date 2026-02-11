game_select_gfxop_init_common(gfx_state_t *state, gfx_options_t *options, void *misc_payload)
{
	int i;

	state->options = options;

	if ((state->static_palette = gfxr_interpreter_get_static_palette(state->resstate,
						SCI_VERSION_0,
						&(state->static_palette_entries),
						misc_payload)))
	{
		for (i = 0; i < state->static_palette_entries; i++)
			gfx_alloc_color(state->driver->mode->palette, state->static_palette + i);
	}


	state->visible_map = GFX_MASK_VISUAL;
	gfxop_set_clip_zone(state, gfx_rect(0, 0, 320, 200));

	state->mouse_pointer = state->mouse_pointer_bg = NULL;
	state->mouse_pointer_visible = 0;
	state->control_map = gfx_pixmap_alloc_index_data(gfx_new_pixmap(320, 200, GFX_RESID_NONE, 0, 0));
	state->control_map->flags |= GFX_PIXMAP_FLAG_EXTERNAL_PALETTE;
	state->options = options;
	state->mouse_pointer_in_hw = 0;
	state->disable_dirty = 0;
	state->events = NULL;

	state->pic = state->pic_unscaled = NULL;

	state->pic_nr = -1;

	state->tag_mode = 0;

	state->dirty_rects = NULL;


	return GFX_OK;
}
