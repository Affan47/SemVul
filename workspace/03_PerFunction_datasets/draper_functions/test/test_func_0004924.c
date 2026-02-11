writeln (GMimeFilter *filter, const char *in, const char *end, char *outptr, char **outend)
{
	GMimeFilterHTML *html = (GMimeFilterHTML *) filter;
	const unsigned char *instart = (const unsigned char *) in;
	const unsigned char *inend = (const unsigned char *) end;
	const unsigned char *inptr = instart;

	while (inptr < inend) {
		gunichar u;

		outptr = check_size (filter, outptr, outend, 16);

		u = html_utf8_getc (&inptr, inend);
		switch (u) {
		case 0xffff:
			w(g_warning ("Invalid UTF-8 sequence encountered"));
			return outptr;
			break;
		case '<':
			outptr = g_stpcpy (outptr, "&lt;");
			html->column++;
			break;
		case '>':
			outptr = g_stpcpy (outptr, "&gt;");
			html->column++;
			break;
		case '&':
			outptr = g_stpcpy (outptr, "&amp;");
			html->column++;
			break;
		case '"':
			outptr = g_stpcpy (outptr, "&quot;");
			html->column++;
			break;
		case '\t':
			if (html->flags & (GMIME_FILTER_HTML_CONVERT_SPACES)) {
				do {
					outptr = check_size (filter, outptr, outend, 7);
					outptr = g_stpcpy (outptr, "&nbsp;");
					html->column++;
				} while (html->column % 8);
				break;
			}

		case ' ':
			if (html->flags & GMIME_FILTER_HTML_CONVERT_SPACES) {
				if (inptr == (instart + 1) || (inptr < inend && (*inptr == ' ' || *inptr == '\t'))) {
					outptr = g_stpcpy (outptr, "&nbsp;");
					html->column++;
					break;
				}
			}

		default:
			if (u >= 0x20 && u < 0x80) {
				*outptr++ = (char) (u & 0xff);
			} else {
				if (html->flags & GMIME_FILTER_HTML_ESCAPE_8BIT)
					*outptr++ = '?';
				else
					outptr += sprintf (outptr, "&#%u;", u);
			}
			html->column++;
			break;
		}
	}

	return outptr;
}
