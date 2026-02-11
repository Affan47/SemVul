dump_datetime(char *output, int maxlen, void *value, int len)
{
	struct ast_tm tm;
	unsigned long val = (unsigned long) ntohl(get_unaligned_uint32(value));
	if (len == (int)sizeof(unsigned int)) {
		tm.tm_sec  = (val & 0x1f) << 1;
		tm.tm_min  = (val >> 5) & 0x3f;
		tm.tm_hour = (val >> 11) & 0x1f;
		tm.tm_mday = (val >> 16) & 0x1f;
		tm.tm_mon  = ((val >> 21) & 0x0f) - 1;
		tm.tm_year = ((val >> 25) & 0x7f) + 100;
		ast_strftime(output, maxlen, "%Y-%m-%d  %T", &tm);
	} else
		ast_copy_string(output, "Invalid DATETIME format!", maxlen);
}
