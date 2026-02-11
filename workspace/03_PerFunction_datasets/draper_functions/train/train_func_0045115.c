snd_soc_new_ac97_codec(struct snd_soc_codec *codec,
	unsigned int id, unsigned int id_mask)
{
	struct snd_ac97 *ac97;
	int ret;

	ac97 = snd_soc_alloc_ac97_codec(codec);
	if (IS_ERR(ac97))
		return ac97;

	if (id) {
		ret = snd_ac97_reset(ac97, false, id, id_mask);
		if (ret < 0) {
			dev_err(codec->dev, "Failed to reset AC97 device: %d\n",
				ret);
			goto err_put_device;
		}
	}

	ret = device_add(&ac97->dev);
	if (ret)
		goto err_put_device;

	return ac97;

err_put_device:
	put_device(&ac97->dev);
	return ERR_PTR(ret);
}
