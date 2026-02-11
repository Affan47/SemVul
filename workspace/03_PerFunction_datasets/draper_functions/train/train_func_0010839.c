tpm_nsc_send(struct tpm_chip *chip, u8 * buf, size_t count)
{
	u8 data;
	int i;


	outb(NSC_COMMAND_CANCEL, chip->vendor.base + NSC_COMMAND);

	if (nsc_wait_for_ready(chip) != 0)
		return -EIO;

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_err(&chip->dev, "IBF timeout\n");
		return -EIO;
	}

	outb(NSC_COMMAND_NORMAL, chip->vendor.base + NSC_COMMAND);
	if (wait_for_stat(chip, NSC_STATUS_IBR, NSC_STATUS_IBR, &data) < 0) {
		dev_err(&chip->dev, "IBR timeout\n");
		return -EIO;
	}

	for (i = 0; i < count; i++) {
		if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
			dev_err(&chip->dev,
				"IBF timeout (while writing data)\n");
			return -EIO;
		}
		outb(buf[i], chip->vendor.base + NSC_DATA);
	}

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_err(&chip->dev, "IBF timeout\n");
		return -EIO;
	}
	outb(NSC_COMMAND_EOC, chip->vendor.base + NSC_COMMAND);

	return count;
}
