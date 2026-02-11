Mixer_add_output_channel(MixerObject *self, PyObject *args)
{
	char *name;
	int stereo = 1;
	int system = 0;
	jack_mixer_output_channel_t channel;

	if (! PyArg_ParseTuple(args, "s|bb", &name, &stereo, &system)) return NULL;

	channel = add_output_channel(self->mixer, name, (bool)stereo, (bool)system);

	return OutputChannel_New(channel);
}
