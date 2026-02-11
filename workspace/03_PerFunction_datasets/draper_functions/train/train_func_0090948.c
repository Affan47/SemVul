efi_shutdown_init(void)
{
	if (!efi_enabled(EFI_RUNTIME_SERVICES))
		return -ENODEV;

	if (efi_poweroff_required())
		pm_power_off = efi_power_off;

	return 0;
}
