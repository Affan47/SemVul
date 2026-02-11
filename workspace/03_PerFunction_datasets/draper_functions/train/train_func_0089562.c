gridlee_sh_start(const struct MachineSound *msound)
{

	gridlee_stream = stream_init("Gridlee custom", 100, Machine->sample_rate, 0, gridlee_stream_update);

	if (Machine->sample_rate != 0)
		freq_to_step = (double)(1 << 24) / (double)Machine->sample_rate;

	return 0;
}
