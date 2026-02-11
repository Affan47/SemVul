snd_als300_ac97_read(struct snd_ac97 *ac97,
							unsigned short reg)
{
	int i;
	struct snd_als300 *chip = ac97->private_data;

	for (i = 0; i < 1000; i++) {
		if ((inb(chip->port+AC97_STATUS) & (AC97_BUSY)) == 0)
			break;
		udelay(10);
	}
	outl((reg << 24) | (1 << 31), chip->port+AC97_ACCESS);

	for (i = 0; i < 1000; i++) {
		if ((inb(chip->port+AC97_STATUS) & (AC97_DATA_AVAIL)) != 0)
			break;
		udelay(10);
	}
	return inw(chip->port+AC97_READ);
}
