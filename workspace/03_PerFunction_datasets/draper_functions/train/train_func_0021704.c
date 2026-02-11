saa7164_g_frequency(struct saa7164_port *port, struct v4l2_frequency *f)
{
	if (f->tuner)
		return -EINVAL;

	f->frequency = port->freq;
	return 0;
}
