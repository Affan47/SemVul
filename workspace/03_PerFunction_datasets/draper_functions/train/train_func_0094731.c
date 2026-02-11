match_pattern(const unsigned char *text, const unsigned char *start,
              const unsigned char *end)
{
    const unsigned char *q, *endclass;
    const unsigned char *p = start;
    bool ismeta;
    int matched, width;
    uint32_t c;

    for (; p <= end; p++) {
        if (!*text && *p != '*')
            return ABORT;

        switch (*p) {
        case '\\':
            if (!*++p)
                return ABORT;


        default:
            if (*text++ != *p)
                return false;
            break;

        case '?':
            text += ISUTF8(*text) ? utf8_length(text, NULL) : 1;
            break;

        case '*':


            for (++p; *p == '*'; p++)
                ;


            if (p > end)
                return true;


            ismeta = (*p == '[' || *p == '?' || *p == '\\');
            while (*text) {
                width = ISUTF8(*text) ? utf8_length(text, NULL) : 1;
                if (ismeta) {
                    matched = match_pattern(text, p, end);
                    text += width;
                } else {
                    while (*text && *text != *p) {
                        text += width;
                        width = ISUTF8(*text) ? utf8_length(text, NULL) : 1;
                    }
                    if (!*text)
                        return ABORT;
                    matched = match_pattern(++text, p + 1, end);
                }
                if (matched != false)
                    return matched;
            }
            return ABORT;

        case '[':


            p++;
            q = p + (*p == '^') + 1;
            if (q > end)
                return ABORT;
            endclass = memchr(q, ']', (size_t) (end - q + 1));
            if (!endclass)
                return ABORT;


            text += utf8_decode(text, NULL, &c);
            if (!match_class(c, p, endclass - 1))
                return false;
            p = endclass;
            break;
        }
    }

    return (*text == '\0');
}
