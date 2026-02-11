bind_hp_volsw_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	int err = snd_ac97_put_volsw(kcontrol, ucontrol);
	if (err > 0) {
		unsigned long priv_saved = kcontrol->private_value;
		kcontrol->private_value = (kcontrol->private_value & ~0xff) | AC97_HEADPHONE;
		snd_ac97_put_volsw(kcontrol, ucontrol);
		kcontrol->private_value = priv_saved;
	}
	return err;
}
