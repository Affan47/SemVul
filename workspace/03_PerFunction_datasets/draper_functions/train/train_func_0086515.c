cfg_get_int(char *section, char *subsection, char *param)
{
	char *s_value, *error;
	long l_value;

	if ((s_value = cfg_get_param(section, subsection, param))) {
		l_value = strtol(s_value, &error, 10);
		if (!*s_value || *error || (l_value & ~0x3FFFFFFFL))
			return -1;
		return (int)l_value;
	}

	return -1;
}
