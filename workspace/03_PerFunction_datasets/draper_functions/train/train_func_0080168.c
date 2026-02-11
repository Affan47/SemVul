dump_short(char *output, int maxlen, void *value, int len)
{
	if (len == (int)sizeof(unsigned short))
		snprintf(output, maxlen, "%d", ntohs(get_unaligned_uint16(value)));
	else
		ast_copy_string(output, "Invalid SHORT", maxlen);
}
