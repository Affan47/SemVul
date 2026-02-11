mga_driver_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *) arg;
	drm_mga_private_t *dev_priv = (drm_mga_private_t *) dev->dev_private;
	int status;
	int handled = 0;

	status = MGA_READ(MGA_STATUS);


	if (status & MGA_VLINEPEN) {
		MGA_WRITE(MGA_ICLEAR, MGA_VLINEICLR);
		atomic_inc(&dev_priv->vbl_received);
		drm_handle_vblank(dev, 0);
		handled = 1;
	}


	if (status & MGA_SOFTRAPEN) {
		const u32 prim_start = MGA_READ(MGA_PRIMADDRESS);
		const u32 prim_end = MGA_READ(MGA_PRIMEND);


		MGA_WRITE(MGA_ICLEAR, MGA_SOFTRAPICLR);


		if ((prim_start & ~0x03) != (prim_end & ~0x03))
			MGA_WRITE(MGA_PRIMEND, prim_end);

		atomic_inc(&dev_priv->last_fence_retired);
		wake_up(&dev_priv->fence_queue);
		handled = 1;
	}

	if (handled)
		return IRQ_HANDLED;
	return IRQ_NONE;
}
