snd_es1968_hw_free(struct snd_pcm_substream *substream)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct esschan *chan;

	if (runtime->private_data == NULL)
		return 0;
	chan = runtime->private_data;
	if (chan->memory) {
		snd_es1968_free_memory(chip, chan->memory);
		chan->memory = NULL;
	}
	return 0;
}
