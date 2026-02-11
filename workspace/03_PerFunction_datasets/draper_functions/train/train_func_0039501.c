get_first_cap_ctl(struct hda_codec *codec, int idx, int type)
{
	struct nid_path *path;
	unsigned int ctl;
	int i;

	path = get_input_path(codec, 0, idx);
	if (!path)
		return 0;
	ctl = path->ctls[type];
	if (!ctl)
		return 0;
	for (i = 0; i < idx - 1; i++) {
		path = get_input_path(codec, 0, i);
		if (path && path->ctls[type] == ctl)
			return 0;
	}
	return ctl;
}
