drm_get_pci_domain(struct drm_device *dev)
{
#ifndef __alpha__


	if (dev->if_version < 0x10004)
		return 0;
#endif

	return pci_domain_nr(dev->pdev->bus);
}
