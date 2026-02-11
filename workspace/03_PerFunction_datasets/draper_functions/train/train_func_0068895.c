vx_audio_src_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct vx_core *chip = snd_kcontrol_chip(kcontrol);

	if (chip->type >= VX_TYPE_VXPOCKET) {
		if (ucontrol->value.enumerated.item[0] > 2)
			return -EINVAL;
	} else {
		if (ucontrol->value.enumerated.item[0] > 1)
			return -EINVAL;
	}
	mutex_lock(&chip->mixer_mutex);
	if (chip->audio_source_target != ucontrol->value.enumerated.item[0]) {
		chip->audio_source_target = ucontrol->value.enumerated.item[0];
		vx_sync_audio_source(chip);
		mutex_unlock(&chip->mixer_mutex);
		return 1;
	}
	mutex_unlock(&chip->mixer_mutex);
	return 0;
}
