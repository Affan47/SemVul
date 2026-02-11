tpm_inf_send(struct tpm_chip *chip, u8 * buf, size_t count)
{
	int i;
	int ret;
	u8 count_high, count_low, count_4, count_3, count_2, count_1;


	tpm_data_out(RESET_LP_IRQC_DISABLE, CMD);

	ret = empty_fifo(chip, 1);
	if (ret) {
		dev_err(&chip->dev, "Timeout while clearing FIFO\n");
		return -EIO;
	}

	ret = wait(chip, STAT_XFE);
	if (ret)
		return -EIO;

	count_4 = (count & 0xff000000) >> 24;
	count_3 = (count & 0x00ff0000) >> 16;
	count_2 = (count & 0x0000ff00) >> 8;
	count_1 = (count & 0x000000ff);
	count_high = ((count + 6) & 0xffffff00) >> 8;
	count_low = ((count + 6) & 0x000000ff);


	wait_and_send(chip, TPM_VL_VER);
	wait_and_send(chip, TPM_CTRL_DATA);
	wait_and_send(chip, count_high);
	wait_and_send(chip, count_low);


	wait_and_send(chip, TPM_VL_VER);
	wait_and_send(chip, TPM_VL_CHANNEL_TPM);
	wait_and_send(chip, count_4);
	wait_and_send(chip, count_3);
	wait_and_send(chip, count_2);
	wait_and_send(chip, count_1);


	for (i = 0; i < count; i++) {
		wait_and_send(chip, buf[i]);
	}
	return count;
}
