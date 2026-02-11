init_test_waveform_generator(struct test_waveform_generator *generator, unsigned num_channels)
{
	unsigned i;

	generator->num_channels = num_channels;
	generator->toggle_countdowns = malloc(sizeof(unsigned) * num_channels);
	if(generator->toggle_countdowns == NULL) return -ENOMEM;
	for(i = 0; i < num_channels; ++i)
		generator->toggle_countdowns[i] = i + 1;
	generator->last_output = 0;
	return 0;
}
