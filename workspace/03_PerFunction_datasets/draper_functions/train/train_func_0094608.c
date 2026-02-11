xml_escape_string_internal (char *buf, const char *s,
				       xml_escape_quote_t quote_type)
{
  int c, length = 0;
  int sl = buf ? 8 : 0;

  while ((c = *s++ & 0xFF))
    switch (c)
    {
    case '"':  if (quote_type != XML_ESCAPE_DOUBLE_QUOTE) goto literal;
	       length += snprintf (buf + length, sl, "&quot;"); break;
    case '\'': if (quote_type != XML_ESCAPE_SINGLE_QUOTE) goto literal;
	       length += snprintf (buf + length, sl, "&apos;"); break;
    case '&':  length += snprintf (buf + length, sl, "&amp;");  break;
    case '<':  length += snprintf (buf + length, sl, "&lt;");   break;
    case '>':  length += snprintf (buf + length, sl, "&gt;");   break;
    case 127:  length += snprintf (buf + length, sl, "&#127;"); break;
    case '\t':
    case '\n':
      literal: if (buf)	buf[length] = c; ++length; break;
    default:   if (c >= ' ') goto literal;
	       length += snprintf (buf + length, sl, "&#%d;", c); break;
    }
  if (buf)
    buf[length] = 0;
  return length + 1;
}
