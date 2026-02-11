telephony_calling_stopped_ind(void)
{
	struct audio_device *dev;

	if (fast_connectable)
		manager_set_fast_connectable(FALSE);

	if (ag.ring_timer) {
		g_source_remove(ag.ring_timer);
		ag.ring_timer = 0;
	}

	if (!active_devices)
		return 0;


	dev = active_devices->data;

	if (!dev->headset->slc->pending_ring && !ag.ring_timer)
		return -EINVAL;

	dev->headset->slc->pending_ring = FALSE;

	return 0;
}
