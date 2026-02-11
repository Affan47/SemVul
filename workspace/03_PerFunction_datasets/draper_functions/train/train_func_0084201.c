xlat_cs(CONF_SECTION *cs, char *fmt, char *out, size_t outlen)

{
	const char *value = NULL;


	if (strcmp(fmt, "instance") == 0) {
		value = cf_section_name2(cs);
		if (!value) {
			*out = '\0';
			return 0;
		}
	} else {
		CONF_PAIR *cp;

		cp = cf_pair_find(cs, fmt);
		if (!cp || !(value = cf_pair_value(cp))) {
			*out = '\0';
			return 0;
		}
	}

	strlcpy(out, value, outlen);

	return strlen(out);
}
