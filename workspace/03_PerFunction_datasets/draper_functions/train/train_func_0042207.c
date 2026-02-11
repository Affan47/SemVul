fw_iso_resources_free(struct fw_iso_resources *r)
{
	struct fw_card *card = fw_parent_device(r->unit)->card;
	int bandwidth, channel;

	mutex_lock(&r->mutex);

	if (r->allocated) {
		bandwidth = r->bandwidth + r->bandwidth_overhead;
		fw_iso_resource_manage(card, r->generation, 1uLL << r->channel,
				       &channel, &bandwidth, false);
		if (channel < 0)
			dev_err(&r->unit->device,
				"isochronous resource deallocation failed\n");

		r->allocated = false;
	}

	mutex_unlock(&r->mutex);
}
