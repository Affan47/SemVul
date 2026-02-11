pcxhr_monitor_sw_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int changed = 0;
	int i;

	mutex_lock(&chip->mgr->mixer_mutex);
	for (i = 0; i < 2; i++) {
		if (chip->monitoring_active[i] !=
		    ucontrol->value.integer.value[i]) {
			chip->monitoring_active[i] =
				!!ucontrol->value.integer.value[i];
			changed |= (1<<i);
		}
	}
	if (changed & 0x01)

		pcxhr_update_audio_pipe_level(chip, 0, 0);
	if (changed & 0x02)

		pcxhr_update_audio_pipe_level(chip, 0, 1);

	mutex_unlock(&chip->mgr->mixer_mutex);
	return (changed != 0);
}
