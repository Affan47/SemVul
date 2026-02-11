snd_dt019x_input_sw_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	unsigned char oval;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_read(sb, SB_DT019X_CAPTURE_SW);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	switch (oval & 0x07) {
	case SB_DT019X_CAP_CD:
		ucontrol->value.enumerated.item[0] = 0;
		break;
	case SB_DT019X_CAP_MIC:
		ucontrol->value.enumerated.item[0] = 1;
		break;
	case SB_DT019X_CAP_LINE:
		ucontrol->value.enumerated.item[0] = 2;
		break;
	case SB_DT019X_CAP_MAIN:
		ucontrol->value.enumerated.item[0] = 4;
		break;


	default:
		ucontrol->value.enumerated.item[0] = 4;
		break;
	}
	return 0;
}
