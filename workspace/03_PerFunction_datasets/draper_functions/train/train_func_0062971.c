intel_pmic_install_opregion_handler(struct device *dev, acpi_handle handle,
					struct regmap *regmap,
					struct intel_pmic_opregion_data *d)
{
	acpi_status status;
	struct intel_pmic_opregion *opregion;
	int ret;

	if (!dev || !regmap || !d)
		return -EINVAL;

	if (!handle)
		return -ENODEV;

	opregion = devm_kzalloc(dev, sizeof(*opregion), GFP_KERNEL);
	if (!opregion)
		return -ENOMEM;

	mutex_init(&opregion->lock);
	opregion->regmap = regmap;
	opregion->lpat_table = acpi_lpat_get_conversion_table(handle);

	status = acpi_install_address_space_handler(handle,
						    PMIC_POWER_OPREGION_ID,
						    intel_pmic_power_handler,
						    NULL, opregion);
	if (ACPI_FAILURE(status)) {
		ret = -ENODEV;
		goto out_error;
	}

	status = acpi_install_address_space_handler(handle,
						    PMIC_THERMAL_OPREGION_ID,
						    intel_pmic_thermal_handler,
						    NULL, opregion);
	if (ACPI_FAILURE(status)) {
		acpi_remove_address_space_handler(handle, PMIC_POWER_OPREGION_ID,
						  intel_pmic_power_handler);
		ret = -ENODEV;
		goto out_error;
	}

	opregion->data = d;
	return 0;

out_error:
	acpi_lpat_free_conversion_table(opregion->lpat_table);
	return ret;
}
