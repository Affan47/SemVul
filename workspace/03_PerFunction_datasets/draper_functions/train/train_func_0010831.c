var_cyrusMasterMIB(struct variable *vp,
                oid     *name,
                size_t  *length,
                int     exact,
                size_t  *var_len,
                WriteMethod **write_method)
{

    static long long_ret;
    static char string[SPRINT_MAX_LEN];


    if (header_generic(vp,name,length,exact,var_len,write_method)
	== MATCH_FAILED )
	return NULL;


    switch(vp->magic) {
    case CYRUSMASTERINFODESCR:
	strlcpy(string, "Cyrus IMAP server master process", sizeof(string));
	*var_len = strlen(string);
	return (unsigned char *) string;

    case CYRUSMASTERINFOVERS:
	strlcpy(string, _CYRUS_VERSION, sizeof(string));
	*var_len = strlen(string);
	return (unsigned char *) string;

    case CYRUSMASTERINFOUPTIME:
	long_ret = 100 * (time(NULL) - startTime);
	return (unsigned char *) &long_ret;

    default:
	ERROR_MSG("");
    }
    return NULL;
}
