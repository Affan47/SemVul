dump_to_midi(unsigned char midi_byte)
{
	int fifo_space, x;

	fifo_space = ((x = pas_read(0x1B89)) >> 4) & 0x0f;


	if (fifo_space < 2 && fifo_space != 0)
		return 0;

	pas_write(midi_byte, 0x178A);

	return 1;
}
