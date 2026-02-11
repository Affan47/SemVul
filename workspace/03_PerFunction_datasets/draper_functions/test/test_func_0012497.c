acpi_dev_pm_detach(struct device *dev, bool power_off)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);

	if (adev && dev->pm_domain == &acpi_general_pm_domain) {
		dev->pm_domain = NULL;
		acpi_remove_pm_notifier(adev);
		if (power_off) {


			dev_pm_qos_hide_latency_limit(dev);
			dev_pm_qos_hide_flags(dev);
			acpi_device_wakeup(adev, ACPI_STATE_S0, false);
			acpi_dev_pm_low_power(dev, adev, ACPI_STATE_S0);
		}
	}
}
