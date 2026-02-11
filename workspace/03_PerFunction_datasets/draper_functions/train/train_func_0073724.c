nssutil_escapeQuotesSize(const char *string, char quote, PRBool addquotes)
{
    int escapes = 0, size = 0;
    const char *src;

    size= addquotes ? 2 : 0;
    for (src=string; *src ; src++) {
	if ((*src == quote) || (*src == '\\')) escapes++;
	size++;
    }
    return size+escapes+1;

}
