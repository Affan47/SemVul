acpi_dev_prop_read_single(struct acpi_device *adev, const char *propname,
			      enum dev_prop_type proptype, void *val)
{
	return adev ? acpi_data_prop_read_single(&adev->data, propname, proptype, val) : -EINVAL;
}
