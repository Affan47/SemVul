chromeos_laptop_dmi_matched(const struct dmi_system_id *id)
{
	cros_laptop = (void *)id->driver_data;
	pr_debug("DMI Matched %s.\n", id->ident);


	return 1;
}
