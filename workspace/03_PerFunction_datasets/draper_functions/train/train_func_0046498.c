snd_vt1724_pro_peak_get(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	int idx;

	spin_lock_irq(&ice->reg_lock);
	for (idx = 0; idx < 22; idx++) {
		outb(idx, ICEMT1724(ice, MONITOR_PEAKINDEX));
		ucontrol->value.integer.value[idx] =
			inb(ICEMT1724(ice, MONITOR_PEAKDATA));
	}
	spin_unlock_irq(&ice->reg_lock);
	return 0;
}
