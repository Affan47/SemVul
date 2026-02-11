snd_pcm_multi_hw_params_slave(snd_pcm_t *pcm,
					 unsigned int slave_idx,
					 snd_pcm_hw_params_t *sparams)
{
	snd_pcm_multi_t *multi = pcm->private_data;
	snd_pcm_t *slave = multi->slaves[slave_idx].pcm;
	int err = snd_pcm_hw_params(slave, sparams);
	if (err < 0)
		return err;
	err = snd_pcm_areas_silence(slave->running_areas, 0, slave->channels, slave->buffer_size, slave->format);
	if (err < 0)
		return err;
	if (slave->stopped_areas) {
		err = snd_pcm_areas_silence(slave->stopped_areas, 0, slave->channels, slave->buffer_size, slave->format);
		if (err < 0)
			return err;
	}
	return 0;
}
