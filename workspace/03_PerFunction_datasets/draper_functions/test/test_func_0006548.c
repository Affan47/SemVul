filter_strcpy_special_ext( char *d, char *s, int flags )
{
	for ( ; *s; s++ ) {
		switch ( *s ) {
		case '.':
		case '\\':
		case '[':
		case ']':
		case '*':
		case '+':
		case '^':
		case '$':
			*d++ = '\\';
			break;
		case '(':
		case ')':
		case '}':
		case '{':
		case '|':
		case '?':
			if (flags & FILTER_STRCPY_ESCAPE_RECHARS) {
				*d++ = '\\';
			}
			break;
		default:
			break;
		}
		*d++ = *s;
	}
	*d = '\0';
	return d;
}
