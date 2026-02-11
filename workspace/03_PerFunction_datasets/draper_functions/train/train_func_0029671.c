fill_all_dac_nids(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;

	spec->num_all_dacs = 0;
	memset(spec->all_dacs, 0, sizeof(spec->all_dacs));
	for_each_hda_codec_node(nid, codec) {
		if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_AUD_OUT)
			continue;
		if (spec->num_all_dacs >= ARRAY_SIZE(spec->all_dacs)) {
			codec_err(codec, "Too many DACs!\n");
			break;
		}
		spec->all_dacs[spec->num_all_dacs++] = nid;
	}
}
