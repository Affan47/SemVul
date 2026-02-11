parse_sdvo_panel_data(struct drm_i915_private *dev_priv,
		      const struct bdb_header *bdb)
{
	const struct lvds_dvo_timing *dvo_timing;
	struct drm_display_mode *panel_fixed_mode;
	int index;

	index = i915.vbt_sdvo_panel_type;
	if (index == -2) {
		DRM_DEBUG_KMS("Ignore SDVO panel mode from BIOS VBT tables.\n");
		return;
	}

	if (index == -1) {
		const struct bdb_sdvo_lvds_options *sdvo_lvds_options;

		sdvo_lvds_options = find_section(bdb, BDB_SDVO_LVDS_OPTIONS);
		if (!sdvo_lvds_options)
			return;

		index = sdvo_lvds_options->panel_type;
	}

	dvo_timing = find_section(bdb, BDB_SDVO_PANEL_DTDS);
	if (!dvo_timing)
		return;

	panel_fixed_mode = kzalloc(sizeof(*panel_fixed_mode), GFP_KERNEL);
	if (!panel_fixed_mode)
		return;

	fill_detail_timing_data(panel_fixed_mode, dvo_timing + index);

	dev_priv->vbt.sdvo_lvds_vbt_mode = panel_fixed_mode;

	DRM_DEBUG_KMS("Found SDVO panel mode in BIOS VBT tables:\n");
	drm_mode_debug_printmodeline(panel_fixed_mode);
}
