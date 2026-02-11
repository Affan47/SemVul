do_detailed_mode(struct detailed_timing *timing, void *c)
{
	struct detailed_mode_closure *closure = c;
	struct drm_display_mode *newmode;

	if (timing->pixel_clock) {
		newmode = drm_mode_detailed(closure->connector->dev,
					    closure->edid, timing,
					    closure->quirks);
		if (!newmode)
			return;

		if (closure->preferred)
			newmode->type |= DRM_MODE_TYPE_PREFERRED;


		fixup_detailed_cea_mode_clock(newmode);

		drm_mode_probed_add(closure->connector, newmode);
		closure->modes++;
		closure->preferred = 0;
	}
}
