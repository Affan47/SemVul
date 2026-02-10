snd_es1938_get_byte(struct es1938 *chip)
{
	int i;
	unsigned char v;
	for (i = GET_LOOP_TIMEOUT; i; i--)
		if ((v = inb(SLSB_REG(chip, STATUS))) & 0x80)
			return inb(SLSB_REG(chip, READDATA));
	dev_err(chip->card->dev, "get_byte timeout: status 0x02%x\n", v);
	return -ENODEV;
}
