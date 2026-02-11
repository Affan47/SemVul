snd_ac97_put_spsa(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0xff;
	int mask = (kcontrol->private_value >> 16) & 0xff;

	unsigned short value, old, new;
	int change;

	value = (ucontrol->value.integer.value[0] & mask);

	mutex_lock(&ac97->reg_mutex);
	mask <<= shift;
	value <<= shift;
	old = snd_ac97_read_cache(ac97, reg);
	new = (old & ~mask) | value;
	change = old != new;

	if (change) {
		unsigned short extst = snd_ac97_read_cache(ac97, AC97_EXTENDED_STATUS);
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
		change = snd_ac97_update_bits_nolock(ac97, reg, mask, value);
		if (extst & AC97_EA_SPDIF)
			snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF);
	}
	mutex_unlock(&ac97->reg_mutex);
	return change;
}
