snd_trident_allocate_evoice(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *hw_params)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	struct snd_trident_voice *evoice = voice->extra;


	if (params_buffer_size(hw_params) / 2 != params_period_size(hw_params)) {
		if (evoice == NULL) {
			evoice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
			if (evoice == NULL)
				return -ENOMEM;
			voice->extra = evoice;
			evoice->substream = substream;
		}
	} else {
		if (evoice != NULL) {
			snd_trident_free_voice(trident, evoice);
			voice->extra = evoice = NULL;
		}
	}

	return 0;
}
