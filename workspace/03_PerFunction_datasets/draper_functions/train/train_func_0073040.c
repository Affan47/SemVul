valleyview_irq_preinstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	I915_WRITE(VLV_MASTER_IER, 0);
	POSTING_READ(VLV_MASTER_IER);

	gen5_gt_irq_reset(dev);

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->display_irqs_enabled)
		vlv_display_irq_reset(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);
}
