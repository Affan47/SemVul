i915_enable_pipestat(struct drm_i915_private *dev_priv, enum pipe pipe,
		     u32 status_mask)
{
	u32 enable_mask;

	if (IS_VALLEYVIEW(dev_priv->dev))
		enable_mask = vlv_get_pipestat_enable_mask(dev_priv->dev,
							   status_mask);
	else
		enable_mask = status_mask << 16;
	__i915_enable_pipestat(dev_priv, pipe, enable_mask, status_mask);
}
