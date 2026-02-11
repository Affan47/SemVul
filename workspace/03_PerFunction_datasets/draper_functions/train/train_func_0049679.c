c_gfx_print_dropviews(state_t *s)
{
	if (!_debugstate_valid) {
		sciprintf("Not in debug state\n");
		return 1;
	}

	if (!s->drop_views)
		sciprintf("No dropped dynview list active.\n");
	else
		s->drop_views->print(GFXW(s->drop_views), 0);

	return 0;
}
