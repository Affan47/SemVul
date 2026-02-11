midi_write_event(long cycles, const uint8_t *s, unsigned int n)
{
	if (midi_write_varlen((cycles - cycles_prev) >> 14))
		return 1;

	if (fwrite(s, 1, n, file) != n)
		return 1;

	track_length += n;

	cycles_prev = cycles;
	return 0;
}
