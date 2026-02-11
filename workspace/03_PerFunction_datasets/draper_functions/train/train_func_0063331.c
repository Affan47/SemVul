snd_mts64_ctl_smpte_switch_put(struct snd_kcontrol* kctl,
					  struct snd_ctl_elem_value *uctl)
{
	struct mts64 *mts = snd_kcontrol_chip(kctl);
	int changed = 0;
	int val = !!uctl->value.integer.value[0];

	spin_lock_irq(&mts->lock);
	if (mts->smpte_switch == val)
		goto __out;

	changed = 1;
	mts->smpte_switch = val;
	if (mts->smpte_switch) {
		mts64_smpte_start(mts->pardev->port,
				  mts->time[0], mts->time[1],
				  mts->time[2], mts->time[3],
				  mts->fps);
	} else {
		mts64_smpte_stop(mts->pardev->port);
	}
__out:
	spin_unlock_irq(&mts->lock);
	return changed;
}
