bdw_update_pipe_irq(struct drm_i915_private *dev_priv,
			 enum pipe pipe,
			 uint32_t interrupt_mask,
			 uint32_t enabled_irq_mask)
{
	uint32_t new_val;

	assert_spin_locked(&dev_priv->irq_lock);

	WARN_ON(enabled_irq_mask & ~interrupt_mask);

	if (WARN_ON(!intel_irqs_enabled(dev_priv)))
		return;

	new_val = dev_priv->de_irq_mask[pipe];
	new_val &= ~interrupt_mask;
	new_val |= (~enabled_irq_mask & interrupt_mask);

	if (new_val != dev_priv->de_irq_mask[pipe]) {
		dev_priv->de_irq_mask[pipe] = new_val;
		I915_WRITE(GEN8_DE_PIPE_IMR(pipe), dev_priv->de_irq_mask[pipe]);
		POSTING_READ(GEN8_DE_PIPE_IMR(pipe));
	}
}
