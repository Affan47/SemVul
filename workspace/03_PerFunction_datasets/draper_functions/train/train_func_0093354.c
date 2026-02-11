nexttoken(struct command *cmd, char **line, bool path) {
    char *r, *s, *w;
    char quot = '\0';
    int nbracket = 0;
    int nescaped = 0;
    bool copy;

    s = *line;

    while (*s && isblank(*s)) s+= 1;
    r = s;
    w = s;
    while (*s) {
        copy = true;
        if (*s == '\\') {
            switch (*(s+1)) {
                case '[':
                case ']':
                    nescaped = 2;
                    break;
                case 't':
                    *(s+1) = '\t';
                    nescaped = 1;
                    s += 1;
                    break;
                case 'n':
                    *(s+1) = '\n';
                    nescaped = 1;
                    s += 1;
                    break;
                case ' ':
                case '\t':
                    if (quot) break;
                case '\'':
                case '"':
                    if (quot && quot != *(s+1)) break;
                case '\\':
                    nescaped = 1;
                    s += 1;
                    break;
                default:
                    ERR_REPORT(cmd, AUG_ECMDRUN, "unknown escape sequence");
                    return NULL;
            }
        }

        if (nescaped == 0) {
            if (*s == '[') nbracket += 1;
            if (*s == ']') nbracket -= 1;
            if (nbracket < 0) {
                ERR_REPORT(cmd, AUG_ECMDRUN, "unmatched [");
                return NULL;
            }

            if (!path || nbracket == 0) {
                if (!quot && (*s == '\'' || *s == '"')) {
                    quot = *s;
                    copy = false;
                } else if (quot && *s == quot) {
                    quot = '\0';
                    copy = false;
                }

                if (!quot && isblank(*s))
                    break;
            }
        } else {
            nescaped -= 1;
        }

        if (copy) {
            *w = *s;
            w += 1;
        }
        s += 1;
    }
    if (*s == '\0' && path && nbracket > 0) {
        ERR_REPORT(cmd, AUG_ECMDRUN, "unmatched [");
        return NULL;
    }
    if (*s == '\0' && quot) {
        ERR_REPORT(cmd, AUG_ECMDRUN, "unmatched %c", quot);
        return NULL;
    }
    while (*w && w <= s)
        *w++ = '\0';
    *line = w;
    return r;
}
