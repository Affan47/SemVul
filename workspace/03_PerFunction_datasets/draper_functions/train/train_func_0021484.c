clean_path(char **norm_path)
{
    char **np;

    for (np = norm_path; np && *np; np++)
        slapi_ch_free_string(np);
    slapi_ch_free((void  **)&norm_path);
}
