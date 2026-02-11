intel_tv_mode_lookup(const char *tv_format)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		const struct tv_mode *tv_mode = &tv_modes[i];

		if (!strcmp(tv_format, tv_mode->name))
			return tv_mode;
	}
	return NULL;
}
