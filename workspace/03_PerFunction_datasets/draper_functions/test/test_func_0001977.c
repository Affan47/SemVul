playback_pcm_open(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	ua->playback.substream = substream;
	err = set_stream_hw(ua, substream, ua->playback.channels);
	if (err < 0)
		return err;
	substream->runtime->hw.fifo_size =
		DIV_ROUND_CLOSEST(ua->rate * ua->playback.queue_length,
				  ua->packets_per_second);

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	if (err < 0)
		goto error;
	err = start_usb_playback(ua);
	if (err < 0) {
		if (!test_bit(ALSA_CAPTURE_OPEN, &ua->states))
			stop_usb_capture(ua);
		goto error;
	}
	set_bit(ALSA_PLAYBACK_OPEN, &ua->states);
error:
	mutex_unlock(&ua->mutex);
	return err;
}
