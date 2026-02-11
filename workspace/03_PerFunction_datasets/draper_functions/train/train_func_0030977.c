snd_hda_get_path_idx(struct hda_codec *codec, struct nid_path *path)
{
	struct hda_gen_spec *spec = codec->spec;
	struct nid_path *array = spec->paths.list;
	ssize_t idx;

	if (!spec->paths.used)
		return 0;
	idx = path - array;
	if (idx < 0 || idx >= spec->paths.used)
		return 0;
	return idx + 1;
}
