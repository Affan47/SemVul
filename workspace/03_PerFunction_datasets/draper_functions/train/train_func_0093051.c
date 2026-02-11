intel_xpower_pmic_opregion_probe(struct platform_device *pdev)
{
	struct device *parent = pdev->dev.parent;
	struct axp20x_dev *axp20x = dev_get_drvdata(parent);
	acpi_status status;
	int result;

	status = acpi_install_address_space_handler(ACPI_HANDLE(parent),
			ACPI_ADR_SPACE_GPIO, intel_xpower_pmic_gpio_handler,
			NULL, NULL);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	result = intel_pmic_install_opregion_handler(&pdev->dev,
					ACPI_HANDLE(parent), axp20x->regmap,
					&intel_xpower_pmic_opregion_data);
	if (result)
		acpi_remove_address_space_handler(ACPI_HANDLE(parent),
						  ACPI_ADR_SPACE_GPIO,
						  intel_xpower_pmic_gpio_handler);

	return result;
}
