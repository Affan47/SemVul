capture_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct ua101 *ua = substream->private_data;
	int err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	if (err < 0)
		return err;


	wait_event(ua->alsa_capture_wait,
		   test_bit(CAPTURE_URB_COMPLETED, &ua->states) ||
		   !test_bit(USB_CAPTURE_RUNNING, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states))
		return -ENODEV;
	if (!test_bit(USB_CAPTURE_RUNNING, &ua->states))
		return -EIO;

	ua->capture.period_pos = 0;
	ua->capture.buffer_pos = 0;
	return 0;
}
