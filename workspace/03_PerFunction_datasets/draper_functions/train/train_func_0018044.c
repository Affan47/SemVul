_free_graphics_input(state_t *s)
{
	sciprintf("Freeing graphics\n");

	s->visual->widfree(GFXW(s->visual));

	s->wm_port = s->titlebar_port = s->picture_port = NULL;
	s->visual = NULL;
	s->dyn_views = NULL;
	s->port = NULL;

	if (s->pics)
		sci_free(s->pics);
	s->pics = NULL;
}
