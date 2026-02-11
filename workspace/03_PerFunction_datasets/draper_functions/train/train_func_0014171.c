in_jack_mode_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->private_value;
	unsigned int vref_caps = get_vref_caps(codec, nid);
	unsigned int val, idx;

	val = snd_hda_codec_get_pin_target(codec, nid);
	idx = cvt_from_vref_idx(vref_caps, val & AC_PINCTL_VREFEN);
	if (idx == ucontrol->value.enumerated.item[0])
		return 0;

	val &= ~AC_PINCTL_VREFEN;
	val |= get_vref_idx(vref_caps, ucontrol->value.enumerated.item[0]);
	snd_hda_set_pin_ctl_cache(codec, nid, val);
	return 1;
}
