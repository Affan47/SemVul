midi_gm_allstop(void)
{
	byte data[3] = { 0xc0,
			 0x78,
			 0 };
	int i;


	for (i = 0; i < 16; i++) {
		data[0] = 0xc0 | i;
		writer->write(writer, data, 3);
	}
	if (writer->flush)
		writer->flush(writer);

	return SFX_OK;
}
