snd_cs46xx_ac97_read(struct snd_ac97 * ac97,
					    unsigned short reg)
{
	struct snd_cs46xx *chip = ac97->private_data;
	unsigned short val;
	int codec_index = ac97->num;

	if (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		return 0xffff;

	val = snd_cs46xx_codec_read(chip, reg, codec_index);

	return val;
}
