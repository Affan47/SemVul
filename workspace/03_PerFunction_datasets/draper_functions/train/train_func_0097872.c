handle_resp_for_user(struct fw_card *card, int generation, int source,
		     void *data, size_t length, int *rcode)
{
	struct fw_device *device;
	struct snd_efw *efw;
	unsigned int i;

	spin_lock_irq(&instances_lock);

	for (i = 0; i < SNDRV_CARDS; i++) {
		efw = instances[i];
		if (efw == NULL)
			continue;
		device = fw_parent_device(efw->unit);
		if ((device->card != card) ||
		    (device->generation != generation))
			continue;
		smp_rmb();
		if (device->node_id != source)
			continue;

		break;
	}
	if (i == SNDRV_CARDS)
		goto end;

	copy_resp_to_buf(efw, data, length, rcode);
end:
	spin_unlock_irq(&instances_lock);
}
