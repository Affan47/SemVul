radio_set_freq(float frequency)
{
	if (dev)
		dev->set_freq (dev, frequency);
}
