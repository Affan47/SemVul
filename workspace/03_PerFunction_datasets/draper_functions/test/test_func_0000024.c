call_hold(struct audio_device *dev, const char *buf)
{
	struct headset *hs = dev->headset;
	int err;

	if (strlen(buf) < 9)
		return -EINVAL;

	if (buf[8] != '?') {
		telephony_call_hold_req(dev, &buf[8]);
		return 0;
	}

	err = headset_send(hs, "\r\n+CHLD: (%s)\r\n", ag.chld);
	if (err < 0)
		return err;

	err = headset_send(hs, "\r\nOK\r\n");
	if (err < 0)
		return err;

	if (hs->state != HEADSET_STATE_CONNECTING)
		return 0;

	hfp_slc_complete(dev);

	return 0;
}
