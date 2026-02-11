i810_driver_load(struct drm_device *dev, unsigned long flags)
{

	if (!dev->agp)
		return -EINVAL;

	pci_set_master(dev->pdev);

	return 0;
}
