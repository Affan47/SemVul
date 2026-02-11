make_valid_name(char *result, const char *str)
{
	if (!str || !*str) {
		*result++ = '_';
		*result = '\0';
		return;
	}
	char mc = mapchar[(uint8)*str];
	if (!(mc == '_' || mc == '?' || mc == 'A' || mc == '@')) {
		*result++ = '_';
		str++;
	}
	while (*str) {
		mc = mapchar[(uint8)*str];
		if (mc == '_' || mc == '?' || mc == 'A' || mc == '0' || mc == ':' || mc == '.' || mc == '@') {
			*result++ = *str;
		} else {
			*result++ = '_';
		}
		str++;
	}
	*result = 0;
}
