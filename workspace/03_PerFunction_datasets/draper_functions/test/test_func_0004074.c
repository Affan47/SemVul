dds_init_triangle(void)
{
	int i;

	for (i = 0; i < WAVEFORM_LEN; i++) {
		waveform[i] = rint(offset + amplitude * 2 * triangle((double)i / WAVEFORM_LEN));
	}
}
