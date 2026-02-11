special_dig_in_iface_ctl_get(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *uval)
{
	struct snd_bebob *bebob = snd_kcontrol_chip(kctl);
	struct special_params *params = bebob->maudio_special_quirk;
	unsigned int dig_in_iface;
	int err, val;

	mutex_lock(&bebob->mutex);

	err = avc_audio_get_selector(bebob->unit, 0x00, 0x04,
				     &dig_in_iface);
	if (err < 0) {
		dev_err(&bebob->unit->device,
			"fail to get digital input interface: %d\n", err);
		goto end;
	}


	val = (params->dig_in_fmt << 1) | (dig_in_iface & 0x01);


	if (val > 2)
		val = 2;

	uval->value.enumerated.item[0] = val;
end:
	mutex_unlock(&bebob->mutex);
	return err;
}
