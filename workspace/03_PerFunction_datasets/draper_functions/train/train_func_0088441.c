undo_idling(struct drm_i915_private *dev_priv, bool interruptible)
{
	struct i915_ggtt *ggtt = &dev_priv->ggtt;

	if (unlikely(ggtt->do_idle_maps))
		dev_priv->mm.interruptible = interruptible;
}
