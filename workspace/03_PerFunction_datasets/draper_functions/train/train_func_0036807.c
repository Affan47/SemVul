snd_func_private_card_driver(snd_config_t **dst, snd_config_t *root ATTRIBUTE_UNUSED, snd_config_t *src,
				 snd_config_t *private_data)
{
	char *driver;
	const char *id;
	int err;
	long card;

	err = snd_config_test_id(private_data, "card");
	if (err) {
		SNDERR("field card not found");
		return -EINVAL;
	}
	err = snd_config_get_integer(private_data, &card);
	if (err < 0) {
		SNDERR("field card is not an integer");
		return err;
	}
	if ((err = snd_determine_driver(card, &driver)) < 0)
		return err;
	err = snd_config_get_id(src, &id);
	if (err >= 0)
		err = snd_config_imake_string(dst, id, driver);
	free(driver);
	return err;
}
