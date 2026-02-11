snd_soc_put_xr_sx(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct soc_mreg_control *mc =
		(struct soc_mreg_control *)kcontrol->private_value;
	unsigned int regbase = mc->regbase;
	unsigned int regcount = mc->regcount;
	unsigned int regwshift = component->val_bytes * BITS_PER_BYTE;
	unsigned int regwmask = (1<<regwshift)-1;
	unsigned int invert = mc->invert;
	unsigned long mask = (1UL<<mc->nbits)-1;
	long max = mc->max;
	long val = ucontrol->value.integer.value[0];
	unsigned int i, regval, regmask;
	int err;

	if (invert)
		val = max - val;
	val &= mask;
	for (i = 0; i < regcount; i++) {
		regval = (val >> (regwshift*(regcount-i-1))) & regwmask;
		regmask = (mask >> (regwshift*(regcount-i-1))) & regwmask;
		err = snd_soc_component_update_bits(component, regbase+i,
				regmask, regval);
		if (err < 0)
			return err;
	}

	return 0;
}
