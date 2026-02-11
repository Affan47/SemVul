snd_fm801_codec_read(struct snd_ac97 *ac97, unsigned short reg)
{
	struct fm801 *chip = ac97->private_data;


	if (!fm801_ac97_is_ready(chip, 100)) {
		dev_err(chip->card->dev, "AC'97 interface is busy (1)\n");
		return 0;
	}


	fm801_writew(chip, AC97_CMD,
		     reg | (ac97->addr << FM801_AC97_ADDR_SHIFT) | FM801_AC97_READ);
	if (!fm801_ac97_is_ready(chip, 100)) {
		dev_err(chip->card->dev, "AC'97 interface #%d is busy (2)\n",
			ac97->num);
		return 0;
	}

	if (!fm801_ac97_is_valid(chip, 1000)) {
		dev_err(chip->card->dev,
			"AC'97 interface #%d is not valid (2)\n", ac97->num);
		return 0;
	}

	return fm801_readw(chip, AC97_DATA);
}
