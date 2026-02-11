ap_parse_log_level(const char *str, int *val)
{
    char *err = "Log level keyword must be one of emerg/alert/crit/error/warn/"
                "notice/info/debug/trace1/.../trace8";
    int i = 0;

    if (str == NULL)
        return err;

    while (priorities[i].t_name != NULL) {
        if (!strcasecmp(str, priorities[i].t_name)) {
            *val = priorities[i].t_val;
            return NULL;
        }
        i++;
    }
    return err;
}
