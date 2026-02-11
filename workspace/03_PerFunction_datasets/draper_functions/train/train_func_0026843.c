dmi_save_extended_devices(const struct dmi_header *dm)
{
	const u8 *d = (u8 *) dm + 5;


	if ((*d & 0x80) == 0)
		return;

	dmi_save_dev_onboard(*(d+1), *(u16 *)(d+2), *(d+4), *(d+5),
			     dmi_string_nosave(dm, *(d-1)));
	dmi_save_one_device(*d & 0x7f, dmi_string_nosave(dm, *(d - 1)));
}
