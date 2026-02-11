snd_sb8mixer_put_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int change;
	unsigned char nval, oval;

	if (ucontrol->value.enumerated.item[0] > 2)
		return -EINVAL;
	switch (ucontrol->value.enumerated.item[0]) {
	case 1:
		nval = SB_DSP_MIXS_CD;
		break;
	case 2:
		nval = SB_DSP_MIXS_LINE;
		break;
	default:
		nval = SB_DSP_MIXS_MIC;
	}
	nval <<= 1;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_read(sb, SB_DSP_CAPTURE_SOURCE);
	nval |= oval & ~0x06;
	change = nval != oval;
	if (change)
		snd_sbmixer_write(sb, SB_DSP_CAPTURE_SOURCE, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	return change;
}
