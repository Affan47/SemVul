stac9205_fixup_eapd(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->eapd_switch = 0;
}
