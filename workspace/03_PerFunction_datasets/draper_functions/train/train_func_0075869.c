cfgfile_uaelib (int mode, uae_u32 name, uae_u32 dst, uae_u32 maxlen)
{
	TCHAR tmp[CONFIG_BLEN];
	int i;
	struct strlist *sl;

	if (mode)
		return 0;

	for (i = 0; i < sizeof (tmp) / sizeof (TCHAR); i++) {
		tmp[i] = get_byte (name + i);
		if (tmp[i] == 0)
			break;
	}
	tmp[sizeof(tmp) / sizeof (TCHAR) - 1] = 0;
	if (tmp[0] == 0)
		return 0;
	for (sl = currprefs.all_lines; sl; sl = sl->next) {
		if (!strcasecmp (sl->option, tmp))
			break;
	}

	if (sl) {
		char *s = ua (sl->value);
		for (i = 0; i < maxlen; i++) {
			put_byte (dst + i, s[i]);
			if (s[i] == 0)
				break;
		}
		xfree (s);
		return dst;
	}
	return 0;
}
