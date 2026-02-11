spinand_read_id(struct spi_device *spi_nand, u8 *id)
{
	int retval;
	u8 nand_id[3];
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_READ_ID;
	cmd.n_rx = 3;
	cmd.rx_buf = &nand_id[0];

	retval = spinand_cmd(spi_nand, &cmd);
	if (retval < 0) {
		dev_err(&spi_nand->dev, "error %d reading id\n", retval);
		return retval;
	}
	id[0] = nand_id[1];
	id[1] = nand_id[2];
	return retval;
}
