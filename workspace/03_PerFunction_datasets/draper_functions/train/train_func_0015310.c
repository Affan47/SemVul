via_pin_power_ctl_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct via_spec *spec = codec->spec;
	bool val = !!ucontrol->value.enumerated.item[0];

	if (val == spec->gen.power_down_unused)
		return 0;

	spec->gen.power_down_unused = val;
	analog_low_current_mode(codec);
	return 1;
}
