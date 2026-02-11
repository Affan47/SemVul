string_replace_backslash_codes(const char *a, char *b)
{
	while(*a) {
		if(*a == '\\') {
			a++;
			char c;
			switch (*a) {
			case 'a':
				c = 7;
				break;
			case 'b':
				c = 8;
				break;
			case 't':
				c = 9;
				break;
			case 'n':
				c = 10;
				break;
			case 'v':
				c = 11;
				break;
			case 'f':
				c = 12;
				break;
			case 'r':
				c = 13;
				break;
			default:
				c = *a;
				break;
			}
			*b++ = c;
			a++;
		} else {
			*b++ = *a++;
		}
	}

	*b = 0;
}
