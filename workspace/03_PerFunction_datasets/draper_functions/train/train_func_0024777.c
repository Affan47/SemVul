var_mvxprintf(
    int (*output)(void *ctx, const char *buffer, int bufsize), void *ctx,
    const char *format, va_list ap)
{

    char ibuf[((sizeof(int)*8)/3)+10];
    const char *cp;
    char c;
    int d;
    int n;
    int bytes;

    if (format == NULL)
        return -1;
    bytes = 0;
    while (*format != '\0') {
        if (*format == '%') {
            c = *(format+1);
            if (c == '%') {

                cp = &c;
                n = sizeof(char);
            }
            else if (c == 'c') {

                c = (char)va_arg(ap, int);
                cp = &c;
                n = sizeof(char);
            }
            else if (c == 's') {

                if ((cp = (char *)va_arg(ap, char *)) == NULL)
                    cp = "(null)";
                n = strlen(cp);
            }
            else if (c == 'd') {

                d = (int)va_arg(ap, int);
                bsnprintf(ibuf, sizeof(ibuf), "%d", d);
                cp = ibuf;
                n = strlen(cp);
            }
            else {

                cp = (char *)format;
                n  = 2;
            }
            format += 2;
        }
        else {

            cp = (char *)format;
            if ((format = strchr(cp, '%')) == NULL)
                format = strchr(cp, '\0');
            n = format - cp;
        }

        if (output != NULL)
            if ((n = output(ctx, cp, n)) == -1)
                break;
        bytes += n;
    }
    return bytes;
}
