drm_virtio_set_busid(struct drm_device *dev, struct drm_master *master)
{
	struct pci_dev *pdev = dev->pdev;

	if (pdev) {
		return drm_pci_set_busid(dev, master);
	}
	return 0;
}
