cache_strqtok(char *str, const char *sep, char **last)
{
    char *token;
    int quoted = 0;

    if (!str) {
        str = *last;
    }

    if (!str) {
        return NULL;
    }


    while (*str && ap_strchr_c(sep, *str)) {
        ++str;
    }

    if (!*str) {
        return NULL;
    }

    token = str;


    *last = token;
    while (**last) {
        if (!quoted) {
            if (**last == '\"' && !ap_strchr_c(sep, '\"')) {
                quoted = 1;
                ++*last;
            }
            else if (!ap_strchr_c(sep, **last)) {
                ++*last;
            }
            else {
                break;
            }
        }
        else {
            if (**last == '\"') {
                quoted = 0;
                ++*last;
            }
            else if (**last == '\\') {
                ++*last;
                if (**last) {
                    ++*last;
                }
            }
            else {
                ++*last;
            }
        }
    }

    if (**last) {
        **last = '\0';
        ++*last;
    }

    return token;
}
