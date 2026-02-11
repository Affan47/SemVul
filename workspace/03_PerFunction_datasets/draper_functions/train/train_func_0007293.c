look_for_dev(struct snd_card *card, void *device_data)
{
	struct snd_device *dev;

	list_for_each_entry(dev, &card->devices, list)
		if (dev->device_data == device_data)
			return dev;

	return NULL;
}
