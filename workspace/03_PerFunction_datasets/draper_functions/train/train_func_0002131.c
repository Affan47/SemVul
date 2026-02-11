lola_enable_clock_events(struct lola *chip)
{
	unsigned int res;
	int err;

	err = lola_codec_read(chip, chip->clock.nid,
			      LOLA_VERB_SET_UNSOLICITED_ENABLE,
			      LOLA_UNSOLICITED_ENABLE | LOLA_UNSOLICITED_TAG,
			      0, &res, NULL);
	if (err < 0)
		return err;
	if (res) {
		dev_warn(chip->card->dev, "error in enable_clock_events %d\n",
		       res);
		return -EINVAL;
	}
	return 0;
}
