radeon_switcheroo_set_state(struct pci_dev *pdev, enum vga_switcheroo_state state)
{
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct radeon_device *rdev = dev->dev_private;

	if (radeon_is_px(dev) && state == VGA_SWITCHEROO_OFF)
		return;

	if (state == VGA_SWITCHEROO_ON) {
		unsigned d3_delay = dev->pdev->d3_delay;

		printk(KERN_INFO "radeon: switched on\n");

		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;

		if (d3_delay < 20 && (rdev->px_quirk_flags & RADEON_PX_QUIRK_LONG_WAKEUP))
			dev->pdev->d3_delay = 20;

		radeon_resume_kms(dev, true, true);

		dev->pdev->d3_delay = d3_delay;

		dev->switch_power_state = DRM_SWITCH_POWER_ON;
		drm_kms_helper_poll_enable(dev);
	} else {
		printk(KERN_INFO "radeon: switched off\n");
		drm_kms_helper_poll_disable(dev);
		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;
		radeon_suspend_kms(dev, true, true);
		dev->switch_power_state = DRM_SWITCH_POWER_OFF;
	}
}
