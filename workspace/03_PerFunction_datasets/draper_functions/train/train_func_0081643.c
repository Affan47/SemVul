get_current_volume(snd_pcm_softvol_t *svol)
{
	unsigned int val;
	unsigned int i;

	if (snd_ctl_elem_read(svol->ctl, &svol->elem) < 0)
		return;
	for (i = 0; i < svol->cchannels; i++) {
		val = svol->elem.value.integer.value[i];
		if (val > svol->max_val)
			val = svol->max_val;
		svol->cur_vol[i] = val;
	}
}
