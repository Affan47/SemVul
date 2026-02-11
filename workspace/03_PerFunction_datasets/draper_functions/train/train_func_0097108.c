valleyview_pipestat_irq_ack(struct drm_device *dev, u32 iir,
					u32 pipe_stats[I915_MAX_PIPES])
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe;

	spin_lock(&dev_priv->irq_lock);

	if (!dev_priv->display_irqs_enabled) {
		spin_unlock(&dev_priv->irq_lock);
		return;
	}

	for_each_pipe(dev_priv, pipe) {
		i915_reg_t reg;
		u32 mask, iir_bit = 0;


		mask = PIPE_FIFO_UNDERRUN_STATUS;

		switch (pipe) {
		case PIPE_A:
			iir_bit = I915_DISPLAY_PIPE_A_EVENT_INTERRUPT;
			break;
		case PIPE_B:
			iir_bit = I915_DISPLAY_PIPE_B_EVENT_INTERRUPT;
			break;
		case PIPE_C:
			iir_bit = I915_DISPLAY_PIPE_C_EVENT_INTERRUPT;
			break;
		}
		if (iir & iir_bit)
			mask |= dev_priv->pipestat_irq_mask[pipe];

		if (!mask)
			continue;

		reg = PIPESTAT(pipe);
		mask |= PIPESTAT_INT_ENABLE_MASK;
		pipe_stats[pipe] = I915_READ(reg) & mask;


		if (pipe_stats[pipe] & (PIPE_FIFO_UNDERRUN_STATUS |
					PIPESTAT_INT_STATUS_MASK))
			I915_WRITE(reg, pipe_stats[pipe]);
	}
	spin_unlock(&dev_priv->irq_lock);
}
