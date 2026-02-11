i915_drm_suspend_late(struct drm_device *drm_dev, bool hibernation)
{
	struct drm_i915_private *dev_priv = drm_dev->dev_private;
	bool fw_csr;
	int ret;

	disable_rpm_wakeref_asserts(dev_priv);

	fw_csr = !IS_BROXTON(dev_priv) &&
		suspend_to_idle(dev_priv) && dev_priv->csr.dmc_payload;


	if (!fw_csr)
		intel_power_domains_suspend(dev_priv);

	ret = 0;
	if (IS_BROXTON(dev_priv))
		bxt_enable_dc9(dev_priv);
	else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		hsw_enable_pc8(dev_priv);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_suspend_complete(dev_priv);

	if (ret) {
		DRM_ERROR("Suspend complete failed: %d\n", ret);
		if (!fw_csr)
			intel_power_domains_init_hw(dev_priv, true);

		goto out;
	}

	pci_disable_device(drm_dev->pdev);


	if (!(hibernation && INTEL_INFO(dev_priv)->gen < 6))
		pci_set_power_state(drm_dev->pdev, PCI_D3hot);

	dev_priv->suspended_to_idle = suspend_to_idle(dev_priv);

out:
	enable_rpm_wakeref_asserts(dev_priv);

	return ret;
}
