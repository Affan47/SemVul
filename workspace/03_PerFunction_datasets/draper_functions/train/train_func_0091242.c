i915_do_reset(struct drm_device *dev)
{

	pci_write_config_byte(dev->pdev, I915_GDRST, GRDOM_RESET_ENABLE);
	udelay(20);
	pci_write_config_byte(dev->pdev, I915_GDRST, 0);

	return wait_for(i915_reset_complete(dev), 500);
}
