decodeNVpair(const char *srcstring, char separator, char **name, char **value)
{
    int lpc = 0;
    int len = 0;
    const char *temp = NULL;

    CRM_ASSERT(name != NULL && value != NULL);
    *name = NULL;
    *value = NULL;

    crm_trace("Attempting to decode: [%s]", srcstring);
    if (srcstring != NULL) {
        len = strlen(srcstring);
        while (lpc <= len) {
            if (srcstring[lpc] == separator) {
                *name = calloc(1, lpc + 1);
                if (*name == NULL) {
                    break;
                }
                memcpy(*name, srcstring, lpc);
                (*name)[lpc] = '\0';


                len = len - lpc;
                len--;
                if (len <= 0) {
                    *value = NULL;
                } else {

                    *value = calloc(1, len + 1);
                    if (*value == NULL) {
                        break;
                    }
                    temp = srcstring + lpc + 1;
                    memcpy(*value, temp, len);
                    (*value)[len] = '\0';
                }
                return TRUE;
            }
            lpc++;
        }
    }

    if (*name != NULL) {
        free(*name);
        *name = NULL;
    }
    *name = NULL;
    *value = NULL;

    return FALSE;
}
