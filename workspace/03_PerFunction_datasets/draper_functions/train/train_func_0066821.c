kirkwood_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return kirkwood_i2s_play_trigger(substream, cmd, dai);
	else
		return kirkwood_i2s_rec_trigger(substream, cmd, dai);

	return 0;
}
