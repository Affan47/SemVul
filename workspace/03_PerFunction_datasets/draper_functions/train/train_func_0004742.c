request_locality(struct tpm_chip *chip)
{
	unsigned long stop;
	long ret;
	struct st33zp24_dev *tpm_dev;
	u8 data;

	if (check_locality(chip) == chip->vendor.locality)
		return chip->vendor.locality;

	tpm_dev = (struct st33zp24_dev *)TPM_VPRIV(chip);

	data = TPM_ACCESS_REQUEST_USE;
	ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	if (ret < 0)
		return ret;

	stop = jiffies + chip->vendor.timeout_a;


	do {
		if (check_locality(chip) >= 0)
			return chip->vendor.locality;
		msleep(TPM_TIMEOUT);
	} while (time_before(jiffies, stop));


	return -EACCES;
}
