drm_bridge_mode_fixup(struct drm_bridge *bridge,
			const struct drm_display_mode *mode,
			struct drm_display_mode *adjusted_mode)
{
	bool ret = true;

	if (!bridge)
		return true;

	if (bridge->funcs->mode_fixup)
		ret = bridge->funcs->mode_fixup(bridge, mode, adjusted_mode);

	ret = ret && drm_bridge_mode_fixup(bridge->next, mode, adjusted_mode);

	return ret;
}
