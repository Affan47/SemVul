unquote_c_style(const char *quoted, const char **endp)
{
	const char *sp;
	char *name = NULL, *outp = NULL;
	int count = 0, ch, ac;

#undef EMIT
#define EMIT(c) (outp ? (*outp++ = (c)) : (count++))

	if (*quoted++ != '"')
		return NULL;

	while (1) {

		for (sp = quoted; (ch = *sp++) != '"'; ) {
			if (ch == '\\') {
				switch (ch = *sp++) {
				case 'a': ch = '\a'; break;
				case 'b': ch = '\b'; break;
				case 'f': ch = '\f'; break;
				case 'n': ch = '\n'; break;
				case 'r': ch = '\r'; break;
				case 't': ch = '\t'; break;
				case 'v': ch = '\v'; break;

				case '\\': case '"':
					break;

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':

					ac = ((ch - '0') << 6);
					if ((ch = *sp++) < '0' || '7' < ch)
						return NULL;
					ac |= ((ch - '0') << 3);
					if ((ch = *sp++) < '0' || '7' < ch)
						return NULL;
					ac |= (ch - '0');
					ch = ac;
					break;
				default:
					return NULL;
				}
			}
			EMIT(ch);
		}

		if (name) {
			*outp = 0;
			if (endp)
				*endp = sp;
			return name;
		}
		outp = name = xmalloc(count + 1);
	}
}
