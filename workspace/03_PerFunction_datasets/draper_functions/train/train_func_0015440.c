avrftdi_tpi_write_byte(PROGRAMMER * pgm, unsigned char byte)
{
	uint16_t frame;

	struct ftdi_context* ftdic = to_pdata(pgm)->ftdic;

	unsigned char buffer[] = { MPSSE_DO_WRITE | MPSSE_WRITE_NEG | MPSSE_LSB, 1, 0, 0, 0 };

	frame = tpi_byte2frame(byte);

	buffer[3] = frame & 0xff;
	buffer[4] = frame >> 8;

	log_trace("Byte %02x, frame: %04x, MPSSE: 0x%02x 0x%02x 0x%02x  0x%02x 0x%02x\n",
			byte, frame, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);


	E(ftdi_write_data(ftdic, buffer, sizeof(buffer)) != sizeof(buffer), ftdic);

	return 0;
}
