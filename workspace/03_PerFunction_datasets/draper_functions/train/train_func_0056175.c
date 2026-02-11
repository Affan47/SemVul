snd_es1968_program_wavecache(struct es1968 *chip, struct esschan *es,
					 int channel, u32 addr, int capture)
{
	u32 tmpval = (addr - 0x10) & 0xFFF8;

	if (! capture) {
		if (!(es->fmt & ESS_FMT_16BIT))
			tmpval |= 4;
		if (es->fmt & ESS_FMT_STEREO)
			tmpval |= 2;
	}


	wave_set_register(chip, es->apu[channel] << 3, tmpval);

#ifdef CONFIG_PM_SLEEP
	es->wc_map[channel] = tmpval;
#endif
}
