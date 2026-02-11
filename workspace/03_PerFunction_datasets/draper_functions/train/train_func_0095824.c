snd_cmipci_spdif_stream_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct cmipci *chip = snd_kcontrol_chip(kcontrol);
	int i;

	spin_lock_irq(&chip->reg_lock);
	for (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] = (chip->dig_pcm_status >> (i * 8)) & 0xff;
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}
