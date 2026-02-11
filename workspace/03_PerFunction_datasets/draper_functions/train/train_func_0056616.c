snd_cs46xx_codec_reset (struct snd_ac97 * ac97)
{
	unsigned long end_time;
	int err;


	snd_ac97_write(ac97, AC97_RESET, 0);


	if (ac97->num == CS46XX_PRIMARY_CODEC_INDEX) {
		dev_dbg(ac97->bus->card->dev, "CODEC1 mode %04x\n", 0x0);
		snd_cs46xx_ac97_write(ac97, AC97_CSR_ACMODE, 0x0);
	} else if (ac97->num == CS46XX_SECONDARY_CODEC_INDEX) {
		dev_dbg(ac97->bus->card->dev, "CODEC2 mode %04x\n", 0x3);
		snd_cs46xx_ac97_write(ac97, AC97_CSR_ACMODE, 0x3);
	} else {
		snd_BUG();
	}

	udelay(50);


	end_time = jiffies + HZ;
	do {
		unsigned short ext_mid;


		snd_ac97_read(ac97, AC97_RESET);
		snd_ac97_read(ac97, AC97_VENDOR_ID1);
		snd_ac97_read(ac97, AC97_VENDOR_ID2);

		ext_mid = snd_ac97_read(ac97, AC97_EXTENDED_MID);
		if (ext_mid != 0xffff && (ext_mid & 1) != 0)
			return;


		snd_ac97_write(ac97, AC97_REC_GAIN, 0x8a05);
		if ((err = snd_ac97_read(ac97, AC97_REC_GAIN)) == 0x8a05)
			return;

		msleep(10);
	} while (time_after_eq(end_time, jiffies));

	dev_err(ac97->bus->card->dev,
		"CS46xx secondary codec doesn't respond!\n");
}
