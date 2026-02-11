NSSUTIL_DoubleEscape(const char *string, char quote1, char quote2)
{
    char *round1 = NULL;
    char *retValue = NULL;
    if (string == NULL) {
        goto done;
    }
    round1 = nssutil_escapeQuotes(string, quote1, PR_FALSE);
    if (round1) {
        retValue = nssutil_escapeQuotes(round1, quote2, PR_FALSE);
        PORT_Free(round1);
    }

done:
    if (retValue == NULL) {
        retValue = PORT_Strdup("");
    }
    return retValue;
}
