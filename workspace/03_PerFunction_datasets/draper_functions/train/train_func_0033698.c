nssutil_escapeQuotes(const char *string, char quote, PRBool addquotes)
{
    char *newString = 0;
    int size = 0;
    const char *src;
    char *dest;

    size = nssutil_escapeQuotesSize(string, quote, addquotes);

    dest = newString = PORT_ZAlloc(size);
    if (newString == NULL) {
	return NULL;
    }

    if (addquotes) *dest++=quote;
    for (src=string; *src; src++,dest++) {
	if ((*src == '\\') || (*src == quote)) {
	    *dest++ = '\\';
	}
	*dest = *src;
    }
    if (addquotes) *dest=quote;

    return newString;
}
