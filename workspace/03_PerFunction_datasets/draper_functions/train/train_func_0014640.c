i915_drm_suspend(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	pci_power_t opregion_target_state;
	int error;


	mutex_lock(&dev_priv->modeset_restore_lock);
	dev_priv->modeset_restore = MODESET_SUSPENDED;
	mutex_unlock(&dev_priv->modeset_restore_lock);


	intel_display_set_init_power(dev_priv, true);

	drm_kms_helper_poll_disable(dev);

	pci_save_state(dev->pdev);

	error = i915_gem_suspend(dev);
	if (error) {
		dev_err(&dev->pdev->dev,
			"GEM idle failed, resume might fail\n");
		return error;
	}

	intel_guc_suspend(dev);

	intel_suspend_gt_powersave(dev);


	drm_modeset_lock_all(dev);
	intel_display_suspend(dev);
	drm_modeset_unlock_all(dev);

	intel_dp_mst_suspend(dev);

	intel_runtime_pm_disable_interrupts(dev_priv);
	intel_hpd_cancel_work(dev_priv);

	intel_suspend_encoders(dev_priv);

	intel_suspend_hw(dev);

	i915_gem_suspend_gtt_mappings(dev);

	i915_save_state(dev);

	opregion_target_state = PCI_D3cold;
#if IS_ENABLED(CONFIG_ACPI_SLEEP)
	if (acpi_target_system_state() < ACPI_STATE_S3)
		opregion_target_state = PCI_D1;
#endif
	intel_opregion_notify_adapter(dev, opregion_target_state);

	intel_uncore_forcewake_reset(dev, false);
	intel_opregion_fini(dev);

	intel_fbdev_set_suspend(dev, FBINFO_STATE_SUSPENDED, true);

	dev_priv->suspend_count++;

	intel_display_set_init_power(dev_priv, false);

	return 0;
}
