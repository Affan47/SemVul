snd_rme9652_capture_copy(struct snd_pcm_substream *substream, int channel,
				    snd_pcm_uframes_t pos, void __user *dst, snd_pcm_uframes_t count)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	char *channel_buf;

	if (snd_BUG_ON(pos + count > RME9652_CHANNEL_BUFFER_BYTES / 4))
		return -EINVAL;

	channel_buf = rme9652_channel_buffer_location (rme9652,
						       substream->pstr->stream,
						       channel);
	if (snd_BUG_ON(!channel_buf))
		return -EIO;
	if (copy_to_user(dst, channel_buf + pos * 4, count * 4))
		return -EFAULT;
	return count;
}
