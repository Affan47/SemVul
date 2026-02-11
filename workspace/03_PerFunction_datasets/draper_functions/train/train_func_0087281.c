keycode_find_code(const char *str, size_t len)
{
	size_t i;
	for (i = 0; i < N_ELEMENTS(mappings); i++) {
		if (strncmp(str, mappings[i].desc, len) == 0)
			return mappings[i].code;
	}
	return 0;
}
