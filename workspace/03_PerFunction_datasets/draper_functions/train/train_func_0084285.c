fingerprint_scan_dir(fingerprint_ty *fp, const char *fn)
{
    DIR             *dp;
    string_list_ty  wl;
    string_ty       *s;
    size_t          j;


    dp = opendir(fn);
    if (!dp)
        return -1;
    string_list_constructor(&wl);
    for (;;)
    {
        struct dirent   *dep;

        dep = readdir(dp);
        if (!dep)
            break;
        s = str_from_c(dep->d_name);
        string_list_append(&wl, s);
        str_free(s);
    }
    closedir(dp);


    string_list_sort(&wl);


    for (j = 0; j < wl.nstrings; ++j)
    {
        s = wl.string[j];
        fingerprint_addn(fp, (unsigned char *)s->str_text, s->str_length + 1);
    }
    string_list_destructor(&wl);
    return 0;
}
