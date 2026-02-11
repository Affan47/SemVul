getHashString(SV *opts, char *param, char *def,
                          char *result, int maxLen)
{
    SV **vp;
    char *str;
    STRLEN len;

    if ( !opts || !SvROK(opts)
               || SvTYPE(SvRV(opts)) != SVt_PVHV
               || !(vp = hv_fetch((HV*)SvRV(opts), param, strlen(param), 0))
               || !*vp ) {
        if ( !def )
            return -1;
        strcpy(result, def);
        return 0;
    } else {
        str = (char*)SvPV(*vp, len);
        if ( len >= maxLen ) {
            return -1;
        }
        memcpy(result, str, len);
        result[len] = '\0';
    }
    return 0;
}
