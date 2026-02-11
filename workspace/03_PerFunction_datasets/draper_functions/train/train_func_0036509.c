i915_find_fence_reg(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_fence_reg *reg, *avail;
	int i;


	avail = NULL;
	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		reg = &dev_priv->fence_regs[i];
		if (!reg->obj)
			return reg;

		if (!reg->pin_count)
			avail = reg;
	}

	if (avail == NULL)
		goto deadlock;


	list_for_each_entry(reg, &dev_priv->mm.fence_list, lru_list) {
		if (reg->pin_count)
			continue;

		return reg;
	}

deadlock:

	if (intel_has_pending_fb_unpin(dev))
		return ERR_PTR(-EAGAIN);

	return ERR_PTR(-EDEADLK);
}
