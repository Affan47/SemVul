snd_ali_open(struct snd_pcm_substream *substream, int rec,
			int channel, struct snd_pcm_hardware *phw)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ali_voice *pvoice;

	pvoice = snd_ali_alloc_voice(codec, SNDRV_ALI_VOICE_TYPE_PCM, rec,
				     channel);
	if (!pvoice)
		return -EAGAIN;

	pvoice->substream = substream;
	runtime->private_data = pvoice;
	runtime->private_free = snd_ali_pcm_free_substream;

	runtime->hw = *phw;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				     0, 64*1024);
	return 0;
}
