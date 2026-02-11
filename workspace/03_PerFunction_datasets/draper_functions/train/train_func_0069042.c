patch_cs4210(struct hda_codec *codec)
{
	struct cs_spec *spec;
	int err;

	spec = cs_alloc_spec(codec, CS4210_VENDOR_NID);
	if (!spec)
		return -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;
	spec->gen.automute_hook = cs_automute;

	snd_hda_pick_fixup(codec, cs421x_models, cs421x_fixup_tbl,
			   cs421x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);


	cs4210_pinmux_init(codec);

	err = cs421x_parse_auto_config(codec);
	if (err < 0)
		goto error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	cs_free(codec);
	return err;
}
