snd_rawmidi_conf_generic_id(const char *id)
{
	static const char ids[][8] = {
		"comment",
		"type",
		"hint",
	};
	unsigned int k;

	for (k = 0; k < sizeof ids / sizeof *ids; ++k) {
		if (strcmp(id, ids[k]) == 0)
			return 1;
	}
	return 0;
}
