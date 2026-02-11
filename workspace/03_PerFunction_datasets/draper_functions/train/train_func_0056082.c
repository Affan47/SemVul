mkd_xmlchar(unsigned char c)
{
    switch (c) {
    case '<':   return "&lt;";
    case '>':   return "&gt;";
    case '&':   return "&amp;";
    case '"':   return "&quot;";
    case '\'':  return "&apos;";
    default:    if ( isascii(c) || (c & 0x80) )
		    return 0;
		return "";
    }
}
