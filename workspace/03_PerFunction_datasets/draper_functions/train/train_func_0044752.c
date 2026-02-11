snd_ca0106_pcm_open_playback_channel(struct snd_pcm_substream *substream,
						int channel_id)
{
	struct snd_ca0106 *chip = snd_pcm_substream_chip(substream);
        struct snd_ca0106_channel *channel = &(chip->playback_channels[channel_id]);
	struct snd_ca0106_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);

	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = chip;
	epcm->substream = substream;
        epcm->channel_id=channel_id;

	runtime->private_data = epcm;
	runtime->private_free = snd_ca0106_pcm_free_substream;

	runtime->hw = snd_ca0106_playback_hw;

        channel->emu = chip;
        channel->number = channel_id;

	channel->use = 1;


	channel->epcm = epcm;
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                return err;
	if ((err = snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                return err;
	snd_pcm_set_sync(substream);


	if (channel_id != PCM_FRONT_CHANNEL) {
		err = snd_ca0106_pcm_power_dac(chip, channel_id, 1);
		if (err < 0)
			return err;
	}

	restore_spdif_bits(chip, channel_id);

	return 0;
}
