gfxop_set_clip_zone(gfx_state_t *state, rect_t zone)
{
	int xfact, yfact;
	BASIC_CHECKS(GFX_ERROR);

	DDIRTY(stderr, "-- Setting clip zone %d %d %d %d\n", GFX_PRINT_RECT(zone));

	xfact = state->driver->mode->xfact;
	yfact = state->driver->mode->yfact;

	if (zone.x < MIN_X) {
		zone.xl -= (zone.x - MIN_X);
		zone.x = MIN_X;
	}

	if (zone.y < MIN_Y) {
		zone.yl -= (zone.y - MIN_Y);
		zone.y = MIN_Y;
	}

	if (zone.x + zone.xl > MAX_X)
		zone.xl = MAX_X + 1 - zone.x;

	if (zone.y + zone.yl > MAX_Y)
		zone.yl = MAX_Y + 1 - zone.y;

	memcpy(&(state->clip_zone_unscaled), &zone, sizeof(rect_t));

	state->clip_zone.x = state->clip_zone_unscaled.x * xfact;
	state->clip_zone.y = state->clip_zone_unscaled.y * yfact;
	state->clip_zone.xl = state->clip_zone_unscaled.xl * xfact;
	state->clip_zone.yl = state->clip_zone_unscaled.yl * yfact;

	return GFX_OK;
}
