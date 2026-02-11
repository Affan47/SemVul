ironlake_irq_postinstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 display_mask, extra_mask;

	if (INTEL_INFO(dev)->gen >= 7) {
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE_IVB |
				DE_PCH_EVENT_IVB | DE_PLANEC_FLIP_DONE_IVB |
				DE_PLANEB_FLIP_DONE_IVB |
				DE_PLANEA_FLIP_DONE_IVB | DE_AUX_CHANNEL_A_IVB);
		extra_mask = (DE_PIPEC_VBLANK_IVB | DE_PIPEB_VBLANK_IVB |
			      DE_PIPEA_VBLANK_IVB | DE_ERR_INT_IVB |
			      DE_DP_A_HOTPLUG_IVB);
	} else {
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE | DE_PCH_EVENT |
				DE_PLANEA_FLIP_DONE | DE_PLANEB_FLIP_DONE |
				DE_AUX_CHANNEL_A |
				DE_PIPEB_CRC_DONE | DE_PIPEA_CRC_DONE |
				DE_POISON);
		extra_mask = (DE_PIPEA_VBLANK | DE_PIPEB_VBLANK | DE_PCU_EVENT |
			      DE_PIPEB_FIFO_UNDERRUN | DE_PIPEA_FIFO_UNDERRUN |
			      DE_DP_A_HOTPLUG);
	}

	dev_priv->irq_mask = ~display_mask;

	I915_WRITE(HWSTAM, 0xeffe);

	ibx_irq_pre_postinstall(dev);

	GEN5_IRQ_INIT(DE, dev_priv->irq_mask, display_mask | extra_mask);

	gen5_gt_irq_postinstall(dev);

	ibx_irq_postinstall(dev);

	if (IS_IRONLAKE_M(dev)) {


		spin_lock_irq(&dev_priv->irq_lock);
		ironlake_enable_display_irq(dev_priv, DE_PCU_EVENT);
		spin_unlock_irq(&dev_priv->irq_lock);
	}

	return 0;
}
