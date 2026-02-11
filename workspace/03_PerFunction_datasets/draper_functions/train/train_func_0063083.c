drm_irq_install(struct drm_device *dev, int irq)
{
	int ret;
	unsigned long sh_flags = 0;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		return -EINVAL;

	if (irq == 0)
		return -EINVAL;


	if (!dev->dev_private)
		return -EINVAL;

	if (dev->irq_enabled)
		return -EBUSY;
	dev->irq_enabled = true;

	DRM_DEBUG("irq=%d\n", irq);


	if (dev->driver->irq_preinstall)
		dev->driver->irq_preinstall(dev);


	if (drm_core_check_feature(dev, DRIVER_IRQ_SHARED))
		sh_flags = IRQF_SHARED;

	ret = request_irq(irq, dev->driver->irq_handler,
			  sh_flags, dev->driver->name, dev);

	if (ret < 0) {
		dev->irq_enabled = false;
		return ret;
	}

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		vga_client_register(dev->pdev, (void *)dev, drm_irq_vgaarb_nokms, NULL);


	if (dev->driver->irq_postinstall)
		ret = dev->driver->irq_postinstall(dev);

	if (ret < 0) {
		dev->irq_enabled = false;
		if (!drm_core_check_feature(dev, DRIVER_MODESET))
			vga_client_register(dev->pdev, NULL, NULL, NULL);
		free_irq(irq, dev);
	} else {
		dev->irq = irq;
	}

	return ret;
}
