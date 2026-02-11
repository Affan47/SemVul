service_number(const char *service)
{
	char *endptr = NULL;
	unsigned long val = strtoul(service, &endptr, 10);

	if ((val = strtoul(service, &endptr, 10)) > USHRT_MAX)
		return set_errno(ERANGE);

	if (endptr == service || *endptr != '\0')
		return set_errno(EDOM);

	return (int)val;
}
