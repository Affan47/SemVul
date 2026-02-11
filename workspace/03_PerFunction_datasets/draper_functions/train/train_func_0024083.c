cs46xx_poke_via_dsp (struct snd_cs46xx *chip, u32 address, u32 data)
{
	u32 temp;
	int  i;


	if (address < 0x8000 || address >= 0x9000)
		return -EINVAL;


	temp = ( address << 16 ) | ( address & 0x0000FFFF);

	snd_cs46xx_poke(chip,( SPIOWRITE_SCB_ADDR      << 2), temp);
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 1) << 2), data);
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 2) << 2), data);


	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 6) << 2), SPIOWRITE_SCB_ADDR << 0x10);


	for (i=0; i<25; i++) {
		udelay(125);

		temp =  snd_cs46xx_peek(chip,((SPIOWRITE_SCB_ADDR + 6) << 2));
		if (temp == 0x00000000)
			break;
	}

	if (i == 25) {
		dev_err(chip->card->dev,
			"dsp_spos: SPIOWriteTask not responding\n");
		return -EBUSY;
	}

	return 0;
}
