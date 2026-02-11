scarlett_ctl_get(struct snd_kcontrol *kctl,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	int i, err, val;

	for (i = 0; i < elem->channels; i++) {
		err = snd_usb_get_cur_mix_value(elem, i, i, &val);
		if (err < 0)
			return err;

		val = clamp(val / 256, -128, (int)kctl->private_value) +
				    SND_SCARLETT_LEVEL_BIAS;
		ucontrol->value.integer.value[i] = val;
	}

	return 0;
}
