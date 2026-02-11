find_dock_dependent_device(struct dock_station *ds, struct acpi_device *adev)
{
	struct dock_dependent_device *dd;

	list_for_each_entry(dd, &ds->dependent_devices, list)
		if (adev == dd->adev)
			return dd;

	return NULL;
}
