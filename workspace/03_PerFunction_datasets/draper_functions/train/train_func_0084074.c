ap_escape_quotes(apr_pool_t *p, const char *instring)
{
    int newlen = 0;
    const char *inchr = instring;
    char *outchr, *outstring;


    while (*inchr != '\0') {
        newlen++;
        if (*inchr == '"') {
            newlen++;
        }


        if ((*inchr == '\\') && (inchr[1] != '\0')) {
            inchr++;
            newlen++;
        }
        inchr++;
    }
    outstring = apr_palloc(p, newlen + 1);
    inchr = instring;
    outchr = outstring;


    while (*inchr != '\0') {
        if ((*inchr == '\\') && (inchr[1] != '\0')) {
            *outchr++ = *inchr++;
            *outchr++ = *inchr++;
        }
        if (*inchr == '"') {
            *outchr++ = '\\';
        }
        if (*inchr != '\0') {
            *outchr++ = *inchr++;
        }
    }
    *outchr = '\0';
    return outstring;
}
