acpi_dev_suspend_late(struct device *dev)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	u32 target_state;
	bool wakeup;
	int error;

	if (!adev)
		return 0;

	target_state = acpi_target_system_state();
	wakeup = device_may_wakeup(dev) && acpi_device_can_wakeup(adev);
	error = acpi_device_wakeup(adev, target_state, wakeup);
	if (wakeup && error)
		return error;

	error = acpi_dev_pm_low_power(dev, adev, target_state);
	if (error)
		acpi_device_wakeup(adev, ACPI_STATE_UNKNOWN, false);

	return error;
}
