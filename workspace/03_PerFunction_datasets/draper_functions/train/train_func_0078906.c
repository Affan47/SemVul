snd_cs46xx_codec_write(struct snd_cs46xx *chip,
				   unsigned short reg,
				   unsigned short val,
				   int codec_index)
{
	int count;

	if (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		return;

	chip->active_ctrl(chip, 1);


	snd_cs46xx_pokeBA0(chip, BA0_ACCAD , reg);
	snd_cs46xx_pokeBA0(chip, BA0_ACCDA , val);
	snd_cs46xx_peekBA0(chip, BA0_ACCTL);

	if (codec_index == CS46XX_PRIMARY_CODEC_INDEX) {
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL,  ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
	} else {
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_TC |
				   ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
	}

	for (count = 0; count < 4000; count++) {


		udelay(10);


		if (!(snd_cs46xx_peekBA0(chip, BA0_ACCTL) & ACCTL_DCV)) {
			goto end;
		}
	}
	dev_err(chip->card->dev,
		"AC'97 write problem, codec_index = %d, reg = 0x%x, val = 0x%x\n",
		codec_index, reg, val);
 end:
	chip->active_ctrl(chip, -1);
}
