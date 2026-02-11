set_switch_state(struct ct_mixer *mixer,
		 enum CTALSA_MIXER_CTL type, unsigned char state)
{
	if (state)
		mixer->switch_state |= (0x1 << (type - SWH_MIXER_START));
	else
		mixer->switch_state &= ~(0x1 << (type - SWH_MIXER_START));
}
