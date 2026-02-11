_gfxop_update_box(gfx_state_t *state, rect_t box)
{
	int retval;
	_gfxop_scale_rect(&box, state->driver->mode);

	if ((retval = _gfxop_buffer_propagate_box(state, box, GFX_BUFFER_FRONT))) {
		GFXERROR("Error occured while propagating box (%d,%d,%d,%d) to front buffer\n",
			 box.x, box.y, box.xl, box.yl);
		return retval;
	}
	return GFX_OK;
}
