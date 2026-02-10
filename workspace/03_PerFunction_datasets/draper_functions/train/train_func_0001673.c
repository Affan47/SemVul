mkstring(char *s, int size, ulong flags, const char *opt)
{
	int len;
	int extra;
	int left;
	int right;

	switch (flags & (LONG_DEC|LONG_HEX|INT_HEX|INT_DEC|LONGLONG_HEX|ZERO_FILL))
	{
	case LONG_DEC:
		sprintf(s, "%lu", (ulong)opt);
		break;
	case LONG_HEX:
		sprintf(s, "%lx", (ulong)opt);
		break;
	case (LONG_HEX|ZERO_FILL):
		if (VADDR_PRLEN == 8)
			sprintf(s, "%08lx", (ulong)opt);
		else if (VADDR_PRLEN == 16)
			sprintf(s, "%016lx", (ulong)opt);
		break;
	case INT_DEC:
		sprintf(s, "%u", (uint)((ulong)opt));
		break;
	case INT_HEX:
		sprintf(s, "%x", (uint)((ulong)opt));
		break;
	case LONGLONG_HEX:
		sprintf(s, "%llx", *((ulonglong *)opt));
		break;
	default:
		if (opt)
			strcpy(s, opt);
		break;
	}


	len = strlen(s);
	if (size <= len)
		return(s);
	extra = size - len;

	if (flags & CENTER) {


		if (extra % 2) {
			switch (flags & (LJUST|RJUST))
			{
			default:
			case LJUST:
				right = (extra/2) + 1;
				left = extra/2;
				break;
			case RJUST:
				right = extra/2;
				left = (extra/2) + 1;
				break;
			}
		}
		else
			left = right = extra/2;

		shift_string_right(s, left);
		len = strlen(s);
		memset(s + len, ' ', right);
		s[len + right] = NULLCHAR;

		return(s);
	}

	if (flags & LJUST) {
		len = strlen(s);
		memset(s + len, ' ', extra);
		s[len + extra] = NULLCHAR;
	} else if (flags & RJUST)
		shift_string_right(s, extra);

	return(s);
}
