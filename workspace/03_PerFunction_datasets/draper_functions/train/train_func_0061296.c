unescape_special(void *Result, int resultmaxlen, const char *s)
{
	char *result = (char*)Result;
	char *old = result;
	while (s && *s) {
		if (*s == '\\') {
			s++;
			switch (*s) {
			case '0':
				*result++='\0';
				break;
			case 'a':
				*result++='\a';
				break;
			case 'b':
				*result++='\b';
				break;
			case 'e':
				*result++='\e';
				break;
			case 'f':
				*result++='\f';
				break;
			case 'n':
				*result++='\n';
				break;
			case 'r':
				*result++='\r';
				break;
			case 't':
				*result++='\t';
				break;
			case 'v':
				*result++='\v';
				break;
			case '\\':
				*result++='\\';
				break;
			case '\"':
				*result++='"';
				break;
			case 'x':
				s++;
				byte v = hexdigit(*s) * 16;
				s++;
				v += hexdigit(*s);
				*result++ = (char)v;
			}
			if (!--resultmaxlen) break;
		} else {
			*result++ = *s;
			if (!--resultmaxlen) break;
		}
		s++;
	}
	return result-old;
}
