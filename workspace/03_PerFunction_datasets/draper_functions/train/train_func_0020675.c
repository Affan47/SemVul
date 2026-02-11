parse_string(ZZJSON_CONFIG *config) {
    unsigned int len = 16, pos = 0;
    int c;
    char *str = NULL;

    SKIPWS();
    c = GETC();
    if (c != '"') {
        ERROR("string: expected \" at the start");
        return NULL;
    }

    str = config->malloc(len);
    if (!str) {
        MEMERROR();
        return NULL;
    }
    c = GETC();
    while (c > 0 && c != '"') {
        if (!ALLOW_CONTROL_CHARS && c >= 0 && c <= 31) {
            ERROR("string: control characters not allowed");
            goto errout;
        }
        if (c == '\\') {
            c = GETC();
            switch (c) {
                case 'b': c = '\b'; break;
                case 'f': c = '\f'; break;
                case 'n': c = '\n'; break;
                case 'r': c = '\r'; break;
                case 't': c = '\t'; break;
                case 'u': {
                    UNGETC(c);
                    c = '\\';
                    break;
                }
                case '\\': case '/': case '"':
                          break;
                default:
                    if (!ALLOW_ILLEGAL_ESCAPE) {
                        ERROR("string: illegal escape character");
                        goto errout;
                    }
            }
        }
        str[pos++] = c;
        if (pos == len-1) {
            void *tmp = str;
            len *= 2;
            str = config->realloc(str, len);
            if (!str) {
                MEMERROR();
                str = tmp;
                goto errout;
            }
        }
        c = GETC();
    }
    if (c != '"') {
        ERROR("string: expected \" at the end");
        goto errout;
    }
    str[pos] = 0;
    return str;

errout:
    config->free(str);
    return NULL;
}
