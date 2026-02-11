mpd_parse_sticker(const char *input, size_t *name_length_r)
{
	const char *eq;

	eq = strchr(input, '=');
	if (eq == NULL || eq == input)
		return NULL;

	*name_length_r = eq - input;
	return eq + 1;
}
