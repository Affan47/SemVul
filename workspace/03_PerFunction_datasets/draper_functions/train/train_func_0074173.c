fw_iso_resources_allocate(struct fw_iso_resources *r,
			      unsigned int max_payload_bytes, int speed)
{
	struct fw_card *card = fw_parent_device(r->unit)->card;
	int bandwidth, channel, err;

	if (WARN_ON(r->allocated))
		return -EBADFD;

	r->bandwidth = packet_bandwidth(max_payload_bytes, speed);

retry_after_bus_reset:
	spin_lock_irq(&card->lock);
	r->generation = card->generation;
	r->bandwidth_overhead = current_bandwidth_overhead(card);
	spin_unlock_irq(&card->lock);

	err = wait_isoch_resource_delay_after_bus_reset(card);
	if (err < 0)
		return err;

	mutex_lock(&r->mutex);

	bandwidth = r->bandwidth + r->bandwidth_overhead;
	fw_iso_resource_manage(card, r->generation, r->channels_mask,
			       &channel, &bandwidth, true);
	if (channel == -EAGAIN) {
		mutex_unlock(&r->mutex);
		goto retry_after_bus_reset;
	}
	if (channel >= 0) {
		r->channel = channel;
		r->allocated = true;
	} else {
		if (channel == -EBUSY)
			dev_err(&r->unit->device,
				"isochronous resources exhausted\n");
		else
			dev_err(&r->unit->device,
				"isochronous resource allocation failed\n");
	}

	mutex_unlock(&r->mutex);

	return channel;
}
