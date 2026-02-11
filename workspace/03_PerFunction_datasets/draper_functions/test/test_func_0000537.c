tpm1_chip_unregister(struct tpm_chip *chip)
{
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		return;

	if (chip->bios_dir)
		tpm_bios_log_teardown(chip->bios_dir);

	tpm_sysfs_del_device(chip);
}
