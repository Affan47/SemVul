nouveau_pmops_runtime_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct drm_device *drm_dev = pci_get_drvdata(pdev);
	int ret;

	if (nouveau_runtime_pm == 0) {
		pm_runtime_forbid(dev);
		return -EBUSY;
	}


	if (nouveau_runtime_pm == -1 && !nouveau_is_optimus() && !nouveau_is_v1_dsm()) {
		DRM_DEBUG_DRIVER("failing to power off - not optimus\n");
		pm_runtime_forbid(dev);
		return -EBUSY;
	}

	drm_kms_helper_poll_disable(drm_dev);
	vga_switcheroo_set_dynamic_switch(pdev, VGA_SWITCHEROO_OFF);
	nouveau_switcheroo_optimus_dsm();
	ret = nouveau_do_suspend(drm_dev, true);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_ignore_hotplug(pdev);
	pci_set_power_state(pdev, PCI_D3cold);
	drm_dev->switch_power_state = DRM_SWITCH_POWER_DYNAMIC_OFF;
	return ret;
}
