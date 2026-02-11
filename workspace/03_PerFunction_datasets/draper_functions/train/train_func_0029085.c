tms5220_set_frequency(int frequency)
{

	if (!Machine->sample_rate)
		return;


	if (stream != -1)
		stream_update(stream, 0);
	source_step = (UINT32)((double)(frequency / 80) * (double)FRAC_ONE / (double)Machine->sample_rate);
}
