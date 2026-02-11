issue_thinkpad_cmos_command(int cmos_cmd)
{
	if (!cmos_handle)
		return -ENXIO;

	if (!acpi_evalf(cmos_handle, NULL, NULL, "vd", cmos_cmd))
		return -EIO;

	return 0;
}
