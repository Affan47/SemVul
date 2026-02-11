tpm_chip_unregister(struct tpm_chip *chip)
{
	if (!(chip->flags & TPM_CHIP_FLAG_REGISTERED))
		return;

	if (!(chip->flags & TPM_CHIP_FLAG_TPM2))
		sysfs_remove_link(&chip->dev.parent->kobj, "ppi");

	tpm1_chip_unregister(chip);
	tpm_del_char_device(chip);
}
