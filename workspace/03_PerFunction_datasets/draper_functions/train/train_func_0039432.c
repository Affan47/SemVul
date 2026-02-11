snd_ak4117_create(struct snd_card *card, ak4117_read_t *read, ak4117_write_t *write,
		      const unsigned char pgm[5], void *private_data, struct ak4117 **r_ak4117)
{
	struct ak4117 *chip;
	int err = 0;
	unsigned char reg;
	static struct snd_device_ops ops = {
		.dev_free =     snd_ak4117_dev_free,
	};

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;
	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->read = read;
	chip->write = write;
	chip->private_data = private_data;
	setup_timer(&chip->timer, snd_ak4117_timer, (unsigned long)chip);

	for (reg = 0; reg < 5; reg++)
		chip->regmap[reg] = pgm[reg];
	snd_ak4117_reinit(chip);

	chip->rcs0 = reg_read(chip, AK4117_REG_RCS0) & ~(AK4117_QINT | AK4117_CINT | AK4117_STC);
	chip->rcs1 = reg_read(chip, AK4117_REG_RCS1);
	chip->rcs2 = reg_read(chip, AK4117_REG_RCS2);

	if ((err = snd_device_new(card, SNDRV_DEV_CODEC, chip, &ops)) < 0)
		goto __fail;

	if (r_ak4117)
		*r_ak4117 = chip;
	return 0;

      __fail:
	snd_ak4117_free(chip);
	return err < 0 ? err : -EIO;
}
