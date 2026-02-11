snd_ymfpci_playback_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *hw_params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ymfpci_pcm *ypcm = runtime->private_data;
	int err;

	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;
	if ((err = snd_ymfpci_pcm_voice_alloc(ypcm, params_channels(hw_params))) < 0)
		return err;
	return 0;
}
