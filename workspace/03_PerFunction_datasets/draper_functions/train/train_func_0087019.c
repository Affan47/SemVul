snd_device_register_all(struct snd_card *card)
{
	struct snd_device *dev;
	int err;

	if (snd_BUG_ON(!card))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		err = __snd_device_register(dev);
		if (err < 0)
			return err;
	}
	return 0;
}
