scarlett_ctl_put(struct snd_kcontrol *kctl,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	int i, changed = 0;
	int err, oval, val;

	for (i = 0; i < elem->channels; i++) {
		err = snd_usb_get_cur_mix_value(elem, i, i, &oval);
		if (err < 0)
			return err;

		val = ucontrol->value.integer.value[i] -
			SND_SCARLETT_LEVEL_BIAS;
		val = val * 256;
		if (oval != val) {
			err = snd_usb_set_cur_mix_value(elem, i, i, val);
			if (err < 0)
				return err;

			changed = 1;
		}
	}

	return changed;
}
