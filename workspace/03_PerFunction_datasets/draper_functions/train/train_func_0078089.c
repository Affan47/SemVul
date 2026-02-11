s3_regexec_wrap(regex_t *regex,
           const char *str,
           size_t nmatch,
           regmatch_t pmatch[],
           int eflags)
{
    char *message;
    int size;
    int reg_result;

    reg_result = regexec(regex, str, nmatch, pmatch, eflags);
    if (reg_result != 0 && reg_result != REG_NOMATCH) {
        size = regerror(reg_result, regex, NULL, 0);
        message = g_malloc(size);
        regerror(reg_result, regex, message, size);


        g_critical(_("Regex error: %s"), message);
    }

    return reg_result;
}
