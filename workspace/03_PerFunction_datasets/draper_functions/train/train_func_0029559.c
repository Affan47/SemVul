nv50_pior_mode_fixup(struct drm_encoder *encoder,
		     const struct drm_display_mode *mode,
		     struct drm_display_mode *adjusted_mode)
{
	if (!nv50_encoder_mode_fixup(encoder, mode, adjusted_mode))
		return false;
	adjusted_mode->clock *= 2;
	return true;
}
