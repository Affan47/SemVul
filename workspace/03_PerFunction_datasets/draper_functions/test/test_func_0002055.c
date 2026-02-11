snd_dg00x_probe(struct fw_unit *unit,
			   const struct ieee1394_device_id *entry)
{
	struct snd_card *card;
	struct snd_dg00x *dg00x;
	int err;


	err = snd_card_new(&unit->device, -1, NULL, THIS_MODULE,
			   sizeof(struct snd_dg00x), &card);
	if (err < 0)
		return err;
	card->private_free = dg00x_card_free;


	dg00x = card->private_data;
	dg00x->card = card;
	dg00x->unit = fw_unit_get(unit);

	mutex_init(&dg00x->mutex);
	spin_lock_init(&dg00x->lock);
	init_waitqueue_head(&dg00x->hwdep_wait);

	err = name_card(dg00x);
	if (err < 0)
		goto error;

	err = snd_dg00x_stream_init_duplex(dg00x);
	if (err < 0)
		goto error;

	snd_dg00x_proc_init(dg00x);

	err = snd_dg00x_create_pcm_devices(dg00x);
	if (err < 0)
		goto error;

	err = snd_dg00x_create_midi_devices(dg00x);
	if (err < 0)
		goto error;

	err = snd_dg00x_create_hwdep_device(dg00x);
	if (err < 0)
		goto error;

	err = snd_dg00x_transaction_register(dg00x);
	if (err < 0)
		goto error;

	err = snd_card_register(card);
	if (err < 0)
		goto error;

	dev_set_drvdata(&unit->device, dg00x);

	return err;
error:
	snd_card_free(card);
	return err;
}
