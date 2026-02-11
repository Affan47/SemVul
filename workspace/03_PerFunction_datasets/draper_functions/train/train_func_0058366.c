snd_fm801_resume(struct device *dev)
{
	struct snd_card *card = dev_get_drvdata(dev);
	struct fm801 *chip = card->private_data;
	int i;

	snd_fm801_chip_init(chip, 1);
	snd_ac97_resume(chip->ac97);
	snd_ac97_resume(chip->ac97_sec);
	for (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		outw(chip->saved_regs[i], chip->port + saved_regs[i]);

	snd_power_change_state(card, SNDRV_CTL_POWER_D0);
	return 0;
}
