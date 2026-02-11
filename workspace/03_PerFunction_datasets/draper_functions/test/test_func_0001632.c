snb_wm_latency_quirk(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool changed;


	changed = ilk_increase_wm_latency(dev_priv, dev_priv->wm.pri_latency, 12) |
		ilk_increase_wm_latency(dev_priv, dev_priv->wm.spr_latency, 12) |
		ilk_increase_wm_latency(dev_priv, dev_priv->wm.cur_latency, 12);

	if (!changed)
		return;

	DRM_DEBUG_KMS("WM latency values increased to avoid potential underruns\n");
	intel_print_wm_latency(dev, "Primary", dev_priv->wm.pri_latency);
	intel_print_wm_latency(dev, "Sprite", dev_priv->wm.spr_latency);
	intel_print_wm_latency(dev, "Cursor", dev_priv->wm.cur_latency);
}
