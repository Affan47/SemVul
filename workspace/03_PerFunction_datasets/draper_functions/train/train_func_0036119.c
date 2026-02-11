slapi_re_comp( const char *pat, const char **error )
{
    Slapi_Regex *re_handle = NULL;
    pcre        *re = NULL;
    const char  *myerror = NULL;
    int         erroffset;

    re = pcre_compile(pat, 0, &myerror, &erroffset, NULL);
    if (error) {
        *error = myerror;
    }
    if (re) {
        re_handle = (Slapi_Regex *)slapi_ch_calloc(sizeof(Slapi_Regex), 1);
        re_handle->re_pcre = re;
    }

    return re_handle;
}
