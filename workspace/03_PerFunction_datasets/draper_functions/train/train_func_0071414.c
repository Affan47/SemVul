ast_xml_escape(const char *string, char * const outbuf, const size_t buflen)
{
	char *dst = outbuf;
	char *end = outbuf + buflen - 1;


	if (buflen == 0) {
		return -1;
	}


	while (*string && dst < end) {
		const char *entity = NULL;
		int len = 0;

		switch (*string) {
		case '<':
			entity = "&lt;";
			len = 4;
			break;
		case '&':
			entity = "&amp;";
			len = 5;
			break;
		case '>':

			entity = "&gt;";
			len = 4;
			break;
		case '\'':

			entity = "&apos;";
			len = 6;
			break;
		case '"':

			entity = "&quot;";
			len = 6;
			break;
		default:
			*dst++ = *string++;
			break;
		}

		if (entity) {
			ast_assert(len == strlen(entity));
			if (end - dst < len) {

				break;
			}

			strcpy(dst, entity);
			dst += len;
			++string;
		}
	}

	*dst = '\0';

	return *string == '\0' ? 0 : -1;
}
