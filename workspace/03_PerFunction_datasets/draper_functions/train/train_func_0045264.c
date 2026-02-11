headset_unlock(struct audio_device *dev, headset_lock_t lock)
{
	struct headset *hs = dev->headset;

	if (!(hs->lock & lock))
		return FALSE;

	hs->lock &= ~lock;

	if (hs->lock)
		return TRUE;

	if (hs->state == HEADSET_STATE_PLAYING)
		headset_set_state(dev, HEADSET_STATE_CONNECTED);

	if (hs->auto_dc) {
		if (hs->state == HEADSET_STATE_CONNECTED)
			hs->dc_timer = g_timeout_add_seconds(DC_TIMEOUT,
						(GSourceFunc) hs_dc_timeout,
						dev);
		else
			headset_set_state(dev, HEADSET_STATE_DISCONNECTED);
	}

	return TRUE;
}
