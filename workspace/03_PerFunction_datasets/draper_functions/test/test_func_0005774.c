snd_via82xx_mixer_new(struct via82xx *chip, const char *quirk_override)
{
	struct snd_ac97_template ac97;
	int err;
	static struct snd_ac97_bus_ops ops = {
		.write = snd_via82xx_codec_write,
		.read = snd_via82xx_codec_read,
		.wait = snd_via82xx_codec_wait,
	};

	if ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		return err;
	chip->ac97_bus->private_free = snd_via82xx_mixer_free_ac97_bus;
	chip->ac97_bus->clock = chip->ac97_clock;

	memset(&ac97, 0, sizeof(ac97));
	ac97.private_data = chip;
	ac97.private_free = snd_via82xx_mixer_free_ac97;
	ac97.pci = chip->pci;
	ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWER_SAVE;
	if ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		return err;

	snd_ac97_tune_hardware(chip->ac97, ac97_quirks, quirk_override);

	if (chip->chip_type != TYPE_VIA686) {

		snd_ac97_update_bits(chip->ac97, AC97_EXTENDED_STATUS, 0x03 << 4, 0x03 << 4);
	}

	return 0;
}
