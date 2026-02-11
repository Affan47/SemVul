parse_tcp_option(const char *option, uint8_t *result)
{
	unsigned int ret;

	if (!xtables_strtoui(option, NULL, &ret, 1, UINT8_MAX))
		xtables_error(PARAMETER_PROBLEM, "Bad TCP option \"%s\"", option);

	*result = ret;
}
