stac9460_mic_sw_put(struct snd_kcontrol *kcontrol,
	       		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char new, old;
	int change;
	old = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	new = (ucontrol->value.enumerated.item[0] << 7 & 0x80) | (old & ~0x80);
	change = (new != old);
	if (change)
		stac9460_put(ice, STAC946X_GENERAL_PURPOSE, new);
	return change;
}
