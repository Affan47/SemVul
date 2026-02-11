via_driver_irq_preinstall(struct drm_device *dev)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	u32 status;
	drm_via_irq_t *cur_irq;
	int i;

	DRM_DEBUG("dev_priv: %p\n", dev_priv);
	if (dev_priv) {
		cur_irq = dev_priv->via_irqs;

		dev_priv->irq_enable_mask = VIA_IRQ_VBLANK_ENABLE;
		dev_priv->irq_pending_mask = VIA_IRQ_VBLANK_PENDING;

		if (dev_priv->chipset == VIA_PRO_GROUP_A ||
		    dev_priv->chipset == VIA_DX9_0) {
			dev_priv->irq_masks = via_pro_group_a_irqs;
			dev_priv->num_irqs = via_num_pro_group_a;
			dev_priv->irq_map = via_irqmap_pro_group_a;
		} else {
			dev_priv->irq_masks = via_unichrome_irqs;
			dev_priv->num_irqs = via_num_unichrome;
			dev_priv->irq_map = via_irqmap_unichrome;
		}

		for (i = 0; i < dev_priv->num_irqs; ++i) {
			atomic_set(&cur_irq->irq_received, 0);
			cur_irq->enable_mask = dev_priv->irq_masks[i][0];
			cur_irq->pending_mask = dev_priv->irq_masks[i][1];
			init_waitqueue_head(&cur_irq->irq_queue);
			dev_priv->irq_enable_mask |= cur_irq->enable_mask;
			dev_priv->irq_pending_mask |= cur_irq->pending_mask;
			cur_irq++;

			DRM_DEBUG("Initializing IRQ %d\n", i);
		}

		dev_priv->last_vblank_valid = 0;


		status = VIA_READ(VIA_REG_INTERRUPT);
		VIA_WRITE(VIA_REG_INTERRUPT, status &
			  ~(dev_priv->irq_enable_mask));


		viadrv_acknowledge_irqs(dev_priv);
	}
}
