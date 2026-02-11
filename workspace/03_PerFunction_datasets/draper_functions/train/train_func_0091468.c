gw_regex_match_real(const Octstr *re, const Octstr *os, const char *file,
                        long line, const char *func)
{
    regex_t *regexp;
    int rc;


    regexp = gw_regex_comp_real(re, REG_EXTENDED|REG_ICASE, file, line, func);
    if (regexp == NULL)
        return 0;


    rc = gw_regex_exec_real(regexp, os, 0, NULL, 0, file, line, func);

    gw_regex_destroy(regexp);

    return (rc == 0) ? 1 : 0;
}
