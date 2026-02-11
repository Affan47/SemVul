snd_intel8x0_ich_chip_cold_reset(struct intel8x0 *chip)
{
	unsigned int cnt;


	if (snd_pci_quirk_lookup(chip->pci, ich_chip_reset_mode))
		return -EIO;

	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	cnt &= ~(ICH_ACLINK | ICH_PCM_246_MASK);


	iputdword(chip, ICHREG(GLOB_CNT), cnt & ~ICH_AC97COLD);
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	udelay(10);
	iputdword(chip, ICHREG(GLOB_CNT), cnt | ICH_AC97COLD);
	msleep(1);
	return 0;
}
