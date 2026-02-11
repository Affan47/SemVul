snd_wm8766_ctl_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	int n = kcontrol->private_value;
	u16 val1, val2;

	if (wm->ctl[n].get)
		wm->ctl[n].get(wm, &val1, &val2);
	else {
		val1 = wm->regs[wm->ctl[n].reg1] & wm->ctl[n].mask1;
		val1 >>= __ffs(wm->ctl[n].mask1);
		if (wm->ctl[n].flags & WM8766_FLAG_STEREO) {
			val2 = wm->regs[wm->ctl[n].reg2] & wm->ctl[n].mask2;
			val2 >>= __ffs(wm->ctl[n].mask2);
			if (wm->ctl[n].flags & WM8766_FLAG_VOL_UPDATE)
				val2 &= ~WM8766_VOL_UPDATE;
		}
	}
	if (wm->ctl[n].flags & WM8766_FLAG_INVERT) {
		val1 = wm->ctl[n].max - (val1 - wm->ctl[n].min);
		if (wm->ctl[n].flags & WM8766_FLAG_STEREO)
			val2 = wm->ctl[n].max - (val2 - wm->ctl[n].min);
	}
	ucontrol->value.integer.value[0] = val1;
	if (wm->ctl[n].flags & WM8766_FLAG_STEREO)
		ucontrol->value.integer.value[1] = val2;

	return 0;
}
