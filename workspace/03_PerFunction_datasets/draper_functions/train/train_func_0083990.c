str_istr(str_t *str, ssize_t idx, const char *string)
{
	str_check(str);
	g_assert(string != NULL);

	return str_instr(str, idx, string, strlen(string));
}
