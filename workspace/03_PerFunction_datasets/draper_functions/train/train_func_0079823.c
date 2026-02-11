h5tools_escape(char *s, size_t size)
{
    register size_t i;
    size_t n = HDstrlen(s);
    const char *escape;
    char octal[8];

    for (i = 0; i < n; i++) {
        switch (s[i]) {
        case '\'':
            escape = "\\\'";
            break;
        case '\"':
            escape = "\\\"";
            break;
        case '\\':
            escape = "\\\\";
            break;
        case '\?':
            escape = "\\\?";
            break;
        case '\a':
            escape = "\\a";
            break;
        case '\b':
            escape = "\\b";
            break;
        case '\f':
            escape = "\\f";
            break;
        case '\n':
            escape = "\\n";
            break;
        case '\r':
            escape = "\\r";
            break;
        case '\t':
            escape = "\\t";
            break;
        case '\v':
            escape = "\\v";
            break;
        default:
            if (!isprint(s[i])) {
                HDsnprintf(octal, sizeof(octal), "\\%03o", (unsigned char) s[i]);
                escape = octal;
            }
            else {
                escape = NULL;
            }

            break;
        }

        if (escape) {
            size_t esc_size = HDstrlen(escape);

            if (n + esc_size + 1 > size)

                return NULL;

            HDmemmove(s + i + esc_size, s + i + 1, n - i);
            HDmemcpy(s + i, escape, esc_size);
            n += esc_size - 1;
            i += esc_size;
        }
    }

    return s;
}
