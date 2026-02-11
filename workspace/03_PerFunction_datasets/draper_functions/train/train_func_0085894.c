snd_rme9652_hw_silence(struct snd_pcm_substream *substream, int channel,
				  snd_pcm_uframes_t pos, snd_pcm_uframes_t count)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	char *channel_buf;

	channel_buf = rme9652_channel_buffer_location (rme9652,
						       substream->pstr->stream,
						       channel);
	if (snd_BUG_ON(!channel_buf))
		return -EIO;
	memset(channel_buf + pos * 4, 0, count * 4);
	return count;
}
