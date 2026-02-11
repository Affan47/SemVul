OutputChannel_set_prefader(OutputChannelObject *self, PyObject *value, void *closure)
{
	if (value == Py_True) {
		output_channel_set_prefader(self->output_channel, true);
	} else {
		output_channel_set_prefader(self->output_channel, false);
	}
	return 0;
}
