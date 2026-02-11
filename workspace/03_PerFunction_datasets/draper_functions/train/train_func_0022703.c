mga_g200_emit_state(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned int dirty = sarea_priv->dirty;

	if (sarea_priv->warp_pipe != dev_priv->warp_pipe) {
		mga_g200_emit_pipe(dev_priv);
		dev_priv->warp_pipe = sarea_priv->warp_pipe;
	}

	if (dirty & MGA_UPLOAD_CONTEXT) {
		mga_g200_emit_context(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_CONTEXT;
	}

	if (dirty & MGA_UPLOAD_TEX0) {
		mga_g200_emit_tex0(dev_priv);
		sarea_priv->dirty &= ~MGA_UPLOAD_TEX0;
	}
}
