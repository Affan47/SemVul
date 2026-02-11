hotplug_dock_devices(struct dock_station *ds, u32 event)
{
	struct dock_dependent_device *dd;


	list_for_each_entry(dd, &ds->dependent_devices, list)
		dock_hotplug_event(dd, event, DOCK_CALL_FIXUP);


	list_for_each_entry(dd, &ds->dependent_devices, list)
		dock_hotplug_event(dd, event, DOCK_CALL_HANDLER);


	list_for_each_entry(dd, &ds->dependent_devices, list) {
		struct acpi_device *adev = dd->adev;

		if (!acpi_device_enumerated(adev)) {
			int ret = acpi_bus_scan(adev->handle);
			if (ret)
				dev_dbg(&adev->dev, "scan error %d\n", -ret);
		}
	}
}
