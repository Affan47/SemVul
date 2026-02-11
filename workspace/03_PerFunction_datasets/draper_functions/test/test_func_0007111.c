acpi_ac_notify(struct acpi_device *device, u32 event)
{
	struct acpi_ac *ac = acpi_driver_data(device);

	if (!ac)
		return;

	switch (event) {
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
	case ACPI_AC_NOTIFY_STATUS:
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:


		if (ac_sleep_before_get_state_ms > 0)
			msleep(ac_sleep_before_get_state_ms);

		acpi_ac_get_state(ac);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event,
						  (u32) ac->state);
		acpi_notifier_call_chain(device, event, (u32) ac->state);
		kobject_uevent(&ac->charger->dev.kobj, KOBJ_CHANGE);
	}

	return;
}
