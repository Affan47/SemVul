add_automute_mode_enum(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctl(spec, NULL, &automute_mode_enum))
		return -ENOMEM;
	return 0;
}
