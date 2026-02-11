snd_via8233_dxs_volume_put(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct via82xx *chip = snd_kcontrol_chip(kcontrol);
	unsigned int idx = kcontrol->id.subdevice;
	unsigned long port = chip->port + 0x10 * idx;
	unsigned char val;
	int i, change = 0;

	for (i = 0; i < 2; i++) {
		val = ucontrol->value.integer.value[i];
		if (val > VIA_DXS_MAX_VOLUME)
			val = VIA_DXS_MAX_VOLUME;
		val = VIA_DXS_MAX_VOLUME - val;
		change |= val != chip->playback_volume[idx][i];
		if (change) {
			chip->playback_volume[idx][i] = val;
			outb(val, port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
		}
	}
	return change;
}
