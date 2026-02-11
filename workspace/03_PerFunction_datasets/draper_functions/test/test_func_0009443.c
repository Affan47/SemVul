convert_format(char *fmt)
{
	if (!strcmp(fmt, "STRING"))
		return (char *)"text/plain";
	if (!strcmp(fmt, "UTF8_STRING"))
		return (char *)"text/plain;charset=utf-8";
	return fmt;
}
