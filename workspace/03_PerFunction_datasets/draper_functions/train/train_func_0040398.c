check_locality(struct tpm_chip *chip)
{
	struct st33zp24_dev *tpm_dev;
	u8 data;
	u8 status;

	tpm_dev = (struct st33zp24_dev *)TPM_VPRIV(chip);

	status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	if (status && (data &
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID))
		return chip->vendor.locality;

	return -EACCES;
}
