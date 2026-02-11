midi_mt32_write_block(guint8 *data, unsigned int count)
{
	unsigned int block_start = 0;
	unsigned int i = 0;

	while (i < count) {
		if ((data[i] == 0xF0) && (i != block_start)) {
			midiout_write_delayed_block(data + block_start, i - block_start);
			block_start = i;
		}
		if (data[i] == 0xF7) {
			midiout_write_delayed_block(data + block_start, i - block_start + 1);
			midi_mt32_sysex_delay();
			block_start = i + 1;
		}
		i++;
	}
	if (count >= block_start) {
		if (midiout_write_delayed_block(data + block_start, count - block_start
					) != (count - block_start)) {
			fprintf(stderr, "midi_mt32_write_block(): midiout_write_block failed!\n");
			return 1;
		}
	}

	return 0;
}
