vmw_sou_screen_object_flippable(struct vmw_private *dev_priv,
					    struct drm_crtc *crtc)
{
	struct vmw_screen_object_unit *sou = vmw_crtc_to_sou(crtc);

	if (!sou->base.is_implicit)
		return true;

	if (dev_priv->sou_priv->num_implicit != 1)
		return false;

	return true;
}
