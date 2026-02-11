automute_mode_get(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	unsigned int val = 0;
	if (spec->automute_speaker)
		val++;
	if (spec->automute_lo)
		val++;

	ucontrol->value.enumerated.item[0] = val;
	return 0;
}
