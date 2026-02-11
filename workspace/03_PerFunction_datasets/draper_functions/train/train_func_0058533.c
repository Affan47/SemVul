spi_write_flash_status(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int retval;
	u8 ins, status, ewsr;

	ins = srb->cmnd[3];
	status = srb->cmnd[4];
	ewsr = srb->cmnd[5];

	retval = spi_set_init_para(chip);
	if (retval != STATUS_SUCCESS) {
		spi_set_err_code(chip, SPI_HW_ERR);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = sf_enable_write(chip, ewsr);
	if (retval != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF, status);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		SPI_TRANSFER0_START | SPI_CDO_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	if (retval != STATUS_SUCCESS) {
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}
