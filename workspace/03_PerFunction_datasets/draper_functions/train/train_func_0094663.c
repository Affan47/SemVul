spinand_set_otp(struct spi_device *spi_nand, u8 *otp)
{
	int retval;
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_WRITE_REG,
	cmd.n_addr = 1,
	cmd.addr[0] = REG_OTP,
	cmd.n_tx = 1,
	cmd.tx_buf = otp,

	retval = spinand_cmd(spi_nand, &cmd);
	if (retval < 0)
		dev_err(&spi_nand->dev, "error %d set otp\n", retval);

	return retval;
}
