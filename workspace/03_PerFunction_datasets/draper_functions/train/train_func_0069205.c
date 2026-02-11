snd_hdspm_put_playback_mixer(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	int change;
	int channel;
	int gain;

	if (!snd_hdspm_use_is_exclusive(hdspm))
		return -EBUSY;

	channel = ucontrol->id.index - 1;

	if (snd_BUG_ON(channel < 0 || channel >= HDSPM_MAX_CHANNELS))
		return -EINVAL;

	gain = ucontrol->value.integer.value[0]*UNITY_GAIN/64;

	spin_lock_irq(&hdspm->lock);
	change =
	    gain != hdspm_read_pb_gain(hdspm, channel,
				       channel);
	if (change)
		hdspm_write_pb_gain(hdspm, channel, channel,
				    gain);
	spin_unlock_irq(&hdspm->lock);
	return change;
}
