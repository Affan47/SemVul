do_line_mic_switch(struct ct_atc *atc, enum CTALSA_MIXER_CTL type)
{

	if (MIXER_LINEIN_C_S == type) {
		atc->select_line_in(atc);
		set_switch_state(atc->mixer, MIXER_MIC_C_S, 0);
		snd_ctl_notify(atc->card, SNDRV_CTL_EVENT_MASK_VALUE,
							&kctls[1]->id);
	} else if (MIXER_MIC_C_S == type) {
		atc->select_mic_in(atc);
		set_switch_state(atc->mixer, MIXER_LINEIN_C_S, 0);
		snd_ctl_notify(atc->card, SNDRV_CTL_EVENT_MASK_VALUE,
							&kctls[0]->id);
	}
}
