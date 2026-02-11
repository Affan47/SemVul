acpi_ut_get_notify_name(u32 notify_value, acpi_object_type type)
{


	if (notify_value <= ACPI_NOTIFY_MAX) {
		return (acpi_gbl_generic_notify[notify_value]);
	}


	if (notify_value <= ACPI_MAX_SYS_NOTIFY) {
		return ("Reserved");
	}


	if (notify_value <= 0x83) {
		switch (type) {
		case ACPI_TYPE_ANY:
		case ACPI_TYPE_DEVICE:
			return (acpi_gbl_device_notify[notify_value - 0x80]);

		case ACPI_TYPE_PROCESSOR:
			return (acpi_gbl_processor_notify[notify_value - 0x80]);

		case ACPI_TYPE_THERMAL:
			return (acpi_gbl_thermal_notify[notify_value - 0x80]);

		default:
			return ("Target object type does not support notifies");
		}
	}


	if (notify_value <= ACPI_MAX_DEVICE_SPECIFIC_NOTIFY) {
		return ("Device-Specific");
	}


	return ("Hardware-Specific");
}
