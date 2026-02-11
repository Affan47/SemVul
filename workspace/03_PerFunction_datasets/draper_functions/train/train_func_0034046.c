mpd_idle_parse_pair(const struct mpd_pair *pair)
{
	assert(pair != NULL);

	if (strcmp(pair->name, "changed") != 0)
		return 0;

	return mpd_idle_name_parse(pair->value);
}
