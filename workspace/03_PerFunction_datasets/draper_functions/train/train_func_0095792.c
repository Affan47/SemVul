qfits_is_float(const char * s)
{
    regex_t re_float;
    int     status;

    if (s==NULL) return 0;
    if (s[0]==0) return 0;
    if (regcomp(&re_float, regex_float, REG_EXTENDED|REG_NOSUB)!=0) {
        qfits_error("internal error: compiling float rule");
        exit(-1);
    }
    status = regexec(&re_float, s, 0, NULL, 0);
    regfree(&re_float);
    return (status) ? 0 : 1;
}
