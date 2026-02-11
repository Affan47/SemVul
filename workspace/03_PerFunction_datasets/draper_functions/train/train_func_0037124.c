spi_init(struct rtsx_chip *chip)
{
	int retval;

	retval = rtsx_write_register(chip, SPI_CONTROL, 0xFF,
				     CS_POLARITY_LOW | DTO_MSB_FIRST | SPI_MASTER | SPI_MODE0 | SPI_AUTO);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}
	retval = rtsx_write_register(chip, SPI_TCTL, EDO_TIMING_MASK,
				     SAMPLE_DELAY_HALF);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}

	return STATUS_SUCCESS;
}
