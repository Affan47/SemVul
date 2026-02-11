NSSUTIL_ArgFetchValue(char *string, int *pcount)
{
    char *end = NSSUTIL_ArgFindEnd(string);
    char *retString, *copyString;
    PRBool lastEscape = PR_FALSE;
    int len;

    len = end - string;
    if (len == 0) {
	*pcount = 0;
	return NULL;
    }

    copyString = retString = (char *)PORT_Alloc(len+1);

    if (*end) len++;
    *pcount = len;
    if (retString == NULL) return NULL;


    if (NSSUTIL_ArgIsQuote(*string)) string++;
    for (; string < end; string++) {
	if (NSSUTIL_ArgIsEscape(*string) && !lastEscape) {
	    lastEscape = PR_TRUE;
	    continue;
	}
	lastEscape = PR_FALSE;
	*copyString++ = *string;
    }
    *copyString = 0;
    return retString;
}
