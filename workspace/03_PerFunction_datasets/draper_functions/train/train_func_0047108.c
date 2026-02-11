special_dig_in_iface_ctl_set(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *uval)
{
	struct snd_bebob *bebob = snd_kcontrol_chip(kctl);
	struct special_params *params = bebob->maudio_special_quirk;
	unsigned int id, dig_in_fmt, dig_in_iface;
	int err;

	id = uval->value.enumerated.item[0];
	if (id >= ARRAY_SIZE(special_dig_in_iface_labels))
		return -EINVAL;


	dig_in_fmt = (id >> 1) & 0x01;
	dig_in_iface = id & 0x01;

	mutex_lock(&bebob->mutex);

	err = avc_maudio_set_special_clk(bebob,
					 params->clk_src,
					 dig_in_fmt,
					 params->dig_out_fmt,
					 params->clk_lock);
	if (err < 0)
		goto end;


	if (params->dig_in_fmt > 0) {
		err = 1;
		goto end;
	}


	err = avc_audio_set_selector(bebob->unit, 0x00, 0x04, dig_in_iface);
	if (err < 0)
		dev_err(&bebob->unit->device,
			"fail to set digital input interface: %d\n", err);
	err = 1;
end:
	special_stream_formation_set(bebob);
	mutex_unlock(&bebob->mutex);
	return err;
}
