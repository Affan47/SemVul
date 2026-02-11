str2desc(const char *string)
{
	size_t i;
	for (i = 0; i < ARRAY_LEN(limits); i++) {
		if (!strcmp(string, limits[i].clicmd))
			return limits[i].desc;
	}
	return "<unknown>";
}
