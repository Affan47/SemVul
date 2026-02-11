print_key(char *buf, int len, char *start, char *key, va_list args)
{
	va_list copy;
	char *pos = start;
	bool res;

	va_copy(copy, args);
	while (TRUE)
	{
		pos = memchr(pos, '%', key - pos);
		if (!pos)
		{
			break;
		}
		pos++;
		switch (*pos)
		{
			case 'd':
				va_arg(copy, int);
				break;
			case 's':
				va_arg(copy, char*);
				break;
			case 'N':
				va_arg(copy, enum_name_t*);
				va_arg(copy, int);
				break;
			case '%':
				break;
			default:
				DBG1(DBG_CFG, "settings with %%%c not supported!", *pos);
				break;
		}
		pos++;
	}
	res = vsnprintf(buf, len, key, copy) < len;
	va_end(copy);
	return res;
}
