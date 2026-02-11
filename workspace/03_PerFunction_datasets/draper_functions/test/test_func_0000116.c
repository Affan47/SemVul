ali_resume(struct device *dev)
{
	struct snd_card *card = dev_get_drvdata(dev);
	struct snd_ali *chip = card->private_data;
	struct snd_ali_image *im;
	int i, j;

	im = chip->image;
	if (!im)
		return 0;

	spin_lock_irq(&chip->reg_lock);

	for (i = 0; i < ALI_CHANNELS; i++) {
		outb(i, ALI_REG(chip, ALI_GC_CIR));
		for (j = 0; j < ALI_CHANNEL_REGS; j++)
			outl(im->channel_regs[i][j], ALI_REG(chip, j*4 + 0xe0));
	}

	for (i = 0; i < ALI_GLOBAL_REGS; i++) {
		if ((i*4 == ALI_MISCINT) || (i*4 == ALI_STOP) ||
		    (i*4 == ALI_START))
			continue;
		outl(im->regs[i], ALI_REG(chip, i*4));
	}


	outl(im->regs[ALI_START >> 2], ALI_REG(chip, ALI_START));

	outl(im->regs[ALI_MISCINT >> 2], ALI_REG(chip, ALI_MISCINT));

	spin_unlock_irq(&chip->reg_lock);

	for (i = 0 ; i < chip->num_of_codecs; i++)
		snd_ac97_resume(chip->ac97[i]);

	snd_power_change_state(card, SNDRV_CTL_POWER_D0);
	return 0;
}
