dmi_memdev_name(u16 handle, const char **bank, const char **device)
{
	int n;

	if (dmi_memdev == NULL)
		return;

	for (n = 0; n < dmi_memdev_nr; n++) {
		if (handle == dmi_memdev[n].handle) {
			*bank = dmi_memdev[n].bank;
			*device = dmi_memdev[n].device;
			break;
		}
	}
}
