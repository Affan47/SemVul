get_param_value(char *p, const char *param_name, int *len) {
    char pn1[3] = {toupper(param_name[0]), tolower(param_name[0]), 0};
    int pn_len = strlen(param_name);
    char *val_end;
    static char *param_sep = "&";

    while (p) {
        if ((strncasecmp(p, param_name, pn_len) == 0) && (p[pn_len] == '='))
            break;
        if (*p) p++;
        p = strpbrk(p, pn1);
    }
    if (p) {
        p += (pn_len + 1);
        *len = strcspn(p, param_sep);
    }
    return p;
}
