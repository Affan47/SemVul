time_parse_monthdays(const char *arg)
{
	char day[3], *err = NULL;
	uint32_t ret = 0;
	unsigned int i;

	while (my_strseg(day, sizeof(day), &arg, ',') != NULL) {
		i = strtoul(day, &err, 0);
		if ((*err != ',' && *err != '\0') || i > 31)
			xtables_error(PARAMETER_PROBLEM,
			           "%s is not a valid day for --monthdays", day);
		ret |= 1 << i;
	}

	return ret;
}
