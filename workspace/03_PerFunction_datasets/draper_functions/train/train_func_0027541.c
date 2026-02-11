snd_emu1010_dac_pads_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int mask = kcontrol->private_value & 0xff;
	unsigned int val, cache;
	val = ucontrol->value.integer.value[0];
	cache = emu->emu1010.dac_pads;
	if (val == 1)
		cache = cache | mask;
	else
		cache = cache & ~mask;
	if (cache != emu->emu1010.dac_pads) {
		snd_emu1010_fpga_write(emu, EMU_HANA_DAC_PADS, cache );
	        emu->emu1010.dac_pads = cache;
	}

	return 0;
}
