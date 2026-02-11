snd_ali5451_spdif_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ali *codec = kcontrol->private_data;
	unsigned int change = 0, spdif_enable = 0;

	spdif_enable = ucontrol->value.integer.value[0] ? 1 : 0;

	spin_lock_irq(&codec->reg_lock);
	switch (kcontrol->private_value) {
	case 0:
		change = (codec->spdif_mask & 0x02) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x02;
				snd_ali_enable_spdif_out(codec);
			} else {
				codec->spdif_mask &= ~(0x02);
				codec->spdif_mask &= ~(0x04);
				snd_ali_disable_spdif_out(codec);
			}
		}
		break;
	case 1:
		change = (codec->spdif_mask & 0x04) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change && (codec->spdif_mask & 0x02)) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x04;
				snd_ali_enable_spdif_chnout(codec);
			} else {
				codec->spdif_mask &= ~(0x04);
				snd_ali_disable_spdif_chnout(codec);
			}
		}
		break;
	case 2:
		change = (codec->spdif_mask & 0x01) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x01;
				snd_ali_enable_spdif_in(codec);
			} else {
				codec->spdif_mask &= ~(0x01);
				snd_ali_disable_spdif_in(codec);
			}
		}
		break;
	default:
		break;
	}
	spin_unlock_irq(&codec->reg_lock);

	return change;
}
