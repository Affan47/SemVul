snd_ak4114_create(struct snd_card *card,
		      ak4114_read_t *read, ak4114_write_t *write,
		      const unsigned char pgm[6], const unsigned char txcsb[5],
		      void *private_data, struct ak4114 **r_ak4114)
{
	struct ak4114 *chip;
	int err = 0;
	unsigned char reg;
	static struct snd_device_ops ops = {
		.dev_free =     snd_ak4114_dev_free,
	};

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;
	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->read = read;
	chip->write = write;
	chip->private_data = private_data;
	INIT_DELAYED_WORK(&chip->work, ak4114_stats);
	atomic_set(&chip->wq_processing, 0);
	mutex_init(&chip->reinit_mutex);

	for (reg = 0; reg < 6; reg++)
		chip->regmap[reg] = pgm[reg];
	for (reg = 0; reg < 5; reg++)
		chip->txcsb[reg] = txcsb[reg];

	ak4114_init_regs(chip);

	chip->rcs0 = reg_read(chip, AK4114_REG_RCS0) & ~(AK4114_QINT | AK4114_CINT);
	chip->rcs1 = reg_read(chip, AK4114_REG_RCS1);

	if ((err = snd_device_new(card, SNDRV_DEV_CODEC, chip, &ops)) < 0)
		goto __fail;

	if (r_ak4114)
		*r_ak4114 = chip;
	return 0;

      __fail:
	snd_ak4114_free(chip);
	return err < 0 ? err : -EIO;
}
