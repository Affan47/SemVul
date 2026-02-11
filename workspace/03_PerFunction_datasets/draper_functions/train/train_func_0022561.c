snd_intel8x0_ali_codec_ready(struct intel8x0 *chip, int mask)
{
	int count = 0;
	for (count = 0; count < 0x7f; count++) {
		int val = igetbyte(chip, ICHREG(ALI_CSPSR));
		if (val & mask)
			return 0;
	}
	if (! chip->in_ac97_init)
		dev_warn(chip->card->dev, "AC97 codec ready timeout.\n");
	return -EBUSY;
}
