gen6_ring_put_irq(struct intel_engine_cs *engine)
{
	struct drm_device *dev = engine->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long flags;

	spin_lock_irqsave(&dev_priv->irq_lock, flags);
	if (--engine->irq_refcount == 0) {
		if (HAS_L3_DPF(dev) && engine->id == RCS)
			I915_WRITE_IMR(engine, ~GT_PARITY_ERROR(dev));
		else
			I915_WRITE_IMR(engine, ~0);
		gen5_disable_gt_irq(dev_priv, engine->irq_enable_mask);
	}
	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);
}
