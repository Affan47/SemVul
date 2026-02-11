c_gfx_draw_cel(state_t *s)
{
	int view = cmd_params[0].val;
	int loop = cmd_params[1].val;
	int cel = cmd_params[2].val;
	int palette = cmd_params[3].val;
	if (!s) {
		sciprintf("Not in debug state!\n");
		return 1;
	}

	gfxop_set_clip_zone(s->gfx_state, gfx_rect_fullscreen);
	gfxop_draw_cel(s->gfx_state, view, loop, cel, gfx_point(160, 100),
		       s->ega_colors[0], palette);
	gfxop_update(s->gfx_state);

	return 0;
}
