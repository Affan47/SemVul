str2val(const char *str, const struct valstr *vs)
{
	int i;

	for (i = 0; vs[i].str != NULL; i++) {
		if (strncasecmp(vs[i].str, str, __maxlen(str, vs[i].str)) == 0)
			return vs[i].val;
	}

	return vs[i].val;
}
