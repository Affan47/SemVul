snd_intel8x0_ali_codec_write(struct snd_ac97 *ac97, unsigned short reg,
					 unsigned short val)
{
	struct intel8x0 *chip = ac97->private_data;

	if (snd_intel8x0_ali_codec_semaphore(chip))
		return;
	iputword(chip, ICHREG(ALI_CPR), val);
	if (ac97->num)
		reg |= ALI_CPR_ADDR_SECONDARY;
	iputword(chip, ICHREG(ALI_CPR_ADDR), reg);
	snd_intel8x0_ali_codec_ready(chip, ALI_CSPSR_WRITE_OK);
}
