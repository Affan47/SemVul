_gfxr_get_cel(gfx_state_t *state, int nr, int *loop, int *cel, int palette)
{
	gfxr_view_t *view = gfxr_get_view(state->resstate, nr, loop, cel, palette);
	gfxr_loop_t *indexed_loop;

	if (!view)
		return NULL;

	if (*loop >= view->loops_nr
	    || *loop < 0) {
		GFXWARN("Attempt to get cel from loop %d/%d inside view %d\n", *loop,
			view->loops_nr, nr);
		return NULL;
	}
	indexed_loop = view->loops + *loop;

	if (*cel >= indexed_loop->cels_nr
	    || *cel < 0) {
		GFXWARN("Attempt to get cel %d/%d from view %d/%d\n", *cel, indexed_loop->cels_nr,
			nr, *loop);
		return NULL;
	}

	return indexed_loop->cels[*cel];
}
