snd_als300_ac97(struct snd_als300 *chip)
{
	struct snd_ac97_bus *bus;
	struct snd_ac97_template ac97;
	int err;
	static struct snd_ac97_bus_ops ops = {
		.write = snd_als300_ac97_write,
		.read = snd_als300_ac97_read,
	};

	if ((err = snd_ac97_bus(chip->card, 0, &ops, NULL, &bus)) < 0)
		return err;

	memset(&ac97, 0, sizeof(ac97));
	ac97.private_data = chip;

	return snd_ac97_mixer(bus, &ac97, &chip->ac97);
}
