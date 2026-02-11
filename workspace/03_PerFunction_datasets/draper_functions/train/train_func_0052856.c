cx_auto_init(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	snd_hda_gen_init(codec);
	if (!spec->dynamic_eapd)
		cx_auto_turn_eapd(codec, spec->num_eapds, spec->eapds, true);

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_INIT);

	return 0;
}
