alc_parse_auto_config(struct hda_codec *codec,
				 const hda_nid_t *ignore_nids,
				 const hda_nid_t *ssid_nids)
{
	struct alc_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;
	int err;

	err = snd_hda_parse_pin_defcfg(codec, cfg, ignore_nids,
				       spec->parse_flags);
	if (err < 0)
		return err;

	if (ssid_nids)
		alc_ssid_check(codec, ssid_nids);

	err = snd_hda_gen_parse_auto_config(codec, cfg);
	if (err < 0)
		return err;

	return 1;
}
