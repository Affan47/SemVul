ad1986a_fixup_eapd(struct hda_codec *codec,
			       const struct hda_fixup *fix, int action)
{
	struct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		codec->inv_eapd = 0;
		spec->gen.keep_eapd_on = 1;
		spec->eapd_nid = 0x1b;
	}
}
