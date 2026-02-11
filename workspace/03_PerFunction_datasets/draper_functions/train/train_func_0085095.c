set_bios_reboot(const struct dmi_system_id *d)
{
	if (reboot_type != BOOT_BIOS) {
		reboot_type = BOOT_BIOS;
		pr_info("%s series board detected. Selecting %s-method for reboots.\n",
			d->ident, "BIOS");
	}
	return 0;
}
