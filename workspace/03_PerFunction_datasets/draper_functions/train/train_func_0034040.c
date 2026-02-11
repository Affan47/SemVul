sbpro_audio_set_channels(int dev, short channels)
{
	sb_devc *devc = audio_devs[dev]->devc;

	if (channels == 1 || channels == 2)
	{
		if (channels != devc->channels)
		{
			devc->channels = channels;
			if (devc->model == MDL_SBPRO && devc->channels == 2)
				sbpro_audio_set_speed(dev, devc->speed);
		}
	}
	return devc->channels;
}
