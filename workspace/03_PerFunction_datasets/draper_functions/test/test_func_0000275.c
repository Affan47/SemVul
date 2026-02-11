__i915_enable_pipestat(struct drm_i915_private *dev_priv, enum pipe pipe,
		       u32 enable_mask, u32 status_mask)
{
	i915_reg_t reg = PIPESTAT(pipe);
	u32 pipestat = I915_READ(reg) & PIPESTAT_INT_ENABLE_MASK;

	assert_spin_locked(&dev_priv->irq_lock);
	WARN_ON(!intel_irqs_enabled(dev_priv));

	if (WARN_ONCE(enable_mask & ~PIPESTAT_INT_ENABLE_MASK ||
		      status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: enable_mask=0x%x, status_mask=0x%x\n",
		      pipe_name(pipe), enable_mask, status_mask))
		return;

	if ((pipestat & enable_mask) == enable_mask)
		return;

	dev_priv->pipestat_irq_mask[pipe] |= status_mask;


	pipestat |= enable_mask | status_mask;
	I915_WRITE(reg, pipestat);
	POSTING_READ(reg);
}
