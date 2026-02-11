snd_rme9652_put_passthru(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	int change;
	unsigned int val;
	int err = 0;

	if (!snd_rme9652_use_is_exclusive(rme9652))
		return -EBUSY;

	val = ucontrol->value.integer.value[0] & 1;
	spin_lock_irq(&rme9652->lock);
	change = (ucontrol->value.integer.value[0] != rme9652->passthru);
	if (change)
		err = rme9652_set_passthru(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	return err ? err : change;
}
