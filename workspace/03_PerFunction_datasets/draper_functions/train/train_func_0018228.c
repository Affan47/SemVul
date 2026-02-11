asus_dmi_check(void)
{
	const char *model;

	model = dmi_get_system_info(DMI_PRODUCT_NAME);
	if (!model)
		return;


	if (strncmp(model, "L1400B", 6) == 0) {
		wlan_status = -1;
	}
}
