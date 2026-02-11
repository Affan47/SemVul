dump_cs4245_registers(struct oxygen *chip,
				  struct snd_info_buffer *buffer)
{
	struct dg *data = chip->model_data;
	unsigned int addr;

	snd_iprintf(buffer, "\nCS4245:");
	cs4245_read_spi(chip, CS4245_INT_STATUS);
	for (addr = 1; addr < ARRAY_SIZE(data->cs4245_shadow); addr++)
		snd_iprintf(buffer, " %02x", data->cs4245_shadow[addr]);
	snd_iprintf(buffer, "\n");
}
