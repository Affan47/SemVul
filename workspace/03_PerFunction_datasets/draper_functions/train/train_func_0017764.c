automute_mode_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;

	switch (ucontrol->value.enumerated.item[0]) {
	case 0:
		if (!spec->automute_speaker && !spec->automute_lo)
			return 0;
		spec->automute_speaker = 0;
		spec->automute_lo = 0;
		break;
	case 1:
		if (spec->automute_speaker_possible) {
			if (!spec->automute_lo && spec->automute_speaker)
				return 0;
			spec->automute_speaker = 1;
			spec->automute_lo = 0;
		} else if (spec->automute_lo_possible) {
			if (spec->automute_lo)
				return 0;
			spec->automute_lo = 1;
		} else
			return -EINVAL;
		break;
	case 2:
		if (!spec->automute_lo_possible || !spec->automute_speaker_possible)
			return -EINVAL;
		if (spec->automute_speaker && spec->automute_lo)
			return 0;
		spec->automute_speaker = 1;
		spec->automute_lo = 1;
		break;
	default:
		return -EINVAL;
	}
	call_update_outputs(codec);
	return 1;
}
