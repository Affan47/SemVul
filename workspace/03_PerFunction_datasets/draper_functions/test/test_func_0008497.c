acpi_init_coherency(struct acpi_device *adev)
{
	unsigned long long cca = 0;
	acpi_status status;
	struct acpi_device *parent = adev->parent;

	if (parent && parent->flags.cca_seen) {


		adev->flags.cca_seen = 1;
		cca = parent->flags.coherent_dma;
	} else {
		status = acpi_evaluate_integer(adev->handle, "_CCA",
					       NULL, &cca);
		if (ACPI_SUCCESS(status))
			adev->flags.cca_seen = 1;
		else if (!IS_ENABLED(CONFIG_ACPI_CCA_REQUIRED))


			cca = 1;
		else
			acpi_handle_debug(adev->handle,
					  "ACPI device is missing _CCA.\n");
	}

	adev->flags.coherent_dma = cca;
}
