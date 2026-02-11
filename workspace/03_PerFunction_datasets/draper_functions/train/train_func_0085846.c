__archive_string_vsprintf(struct archive_string *as, const char *fmt,
    va_list ap)
{
    char long_flag;
    intmax_t s;
    uintmax_t u;
    const char *p, *p2;

    if (__archive_string_ensure(as, 64) == NULL)
        __archive_errx(1, "Out of memory");

    if (fmt == NULL) {
        as->s[0] = 0;
        return;
    }

    for (p = fmt; *p != '\0'; p++) {
        const char *saved_p = p;

        if (*p != '%') {
            archive_strappend_char(as, *p);
            continue;
        }

        p++;

        long_flag = '\0';
        switch(*p) {
        case 'j':
            long_flag = 'j';
            p++;
            break;
        case 'l':
            long_flag = 'l';
            p++;
            break;
        }

        switch (*p) {
        case '%':
            __archive_strappend_char(as, '%');
            break;
        case 'c':
            s = va_arg(ap, int);
            __archive_strappend_char(as, s);
            break;
        case 'd':
            switch(long_flag) {
            case 'j': s = va_arg(ap, intmax_t); break;
            case 'l': s = va_arg(ap, long); break;
            default:  s = va_arg(ap, int); break;
            }
                append_int(as, s, 10);
            break;
        case 's':
            p2 = va_arg(ap, char *);
            archive_strcat(as, p2);
            break;
        case 'o': case 'u': case 'x': case 'X':

            switch(long_flag) {
            case 'j': u = va_arg(ap, uintmax_t); break;
            case 'l': u = va_arg(ap, unsigned long); break;
            default:  u = va_arg(ap, unsigned int); break;
            }

            switch (*p) {
            case 'o': append_uint(as, u, 8); break;
            case 'u': append_uint(as, u, 10); break;
            default: append_uint(as, u, 16); break;
            }
            break;
        default:

            p = saved_p;
            archive_strappend_char(as, *p);
        }
    }
}
