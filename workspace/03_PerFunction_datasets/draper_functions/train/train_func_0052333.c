wait_for_stat(struct tpm_chip *chip, u8 mask, u8 val, u8 * data)
{
	unsigned long stop;


	*data = inb(chip->vendor.base + NSC_STATUS);
	if ((*data & mask) == val)
		return 0;


	stop = jiffies + 10 * HZ;
	do {
		msleep(TPM_TIMEOUT);
		*data = inb(chip->vendor.base + 1);
		if ((*data & mask) == val)
			return 0;
	}
	while (time_before(jiffies, stop));

	return -EBUSY;
}
