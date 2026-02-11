vfglog(const char *format, va_list args)
{


    int numPercents = 0;
    const char *pt = format;
    while(*pt) {
        if (*pt++ == '%') numPercents++;
    }
    char * err;


    if (numPercents > 0) {
        err =  strerror(errno);
        if (err == NULL) {
            err = "Unknown error";
        }
    } else {
        err = "";
    }


    char *buf = new char[strlen(format) + 2 + strlen(err) *
                        numPercents];
    char *p = buf;
    while (*format) {
        if (format[0] == '%' && format[1] == 'm') {
            p += strlen(strcpy(p, err));
            format += 2;
        } else {
            *p++ = *format++;
        }
    }
    (void) strcpy(p, "\n");
    (void) fprintf(stderr, "%s[%d]: ", program_name, getpid());
    (void) vfprintf(stderr, buf, args);
    delete[] buf;
}
