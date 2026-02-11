snd_virmidi_new(struct snd_card *card, int device, struct snd_rawmidi **rrmidi)
{
	struct snd_rawmidi *rmidi;
	struct snd_virmidi_dev *rdev;
	int err;

	*rrmidi = NULL;
	if ((err = snd_rawmidi_new(card, "VirMidi", device,
				   16,
				   16,
				   &rmidi)) < 0)
		return err;
	strcpy(rmidi->name, rmidi->id);
	rdev = kzalloc(sizeof(*rdev), GFP_KERNEL);
	if (rdev == NULL) {
		snd_device_free(card, rmidi);
		return -ENOMEM;
	}
	rdev->card = card;
	rdev->rmidi = rmidi;
	rdev->device = device;
	rdev->client = -1;
	init_rwsem(&rdev->filelist_sem);
	rwlock_init(&rdev->filelist_lock);
	INIT_LIST_HEAD(&rdev->filelist);
	rdev->seq_mode = SNDRV_VIRMIDI_SEQ_DISPATCH;
	rmidi->private_data = rdev;
	rmidi->private_free = snd_virmidi_free;
	rmidi->ops = &snd_virmidi_global_ops;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_virmidi_input_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_virmidi_output_ops);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	*rrmidi = rmidi;
	return 0;
}
