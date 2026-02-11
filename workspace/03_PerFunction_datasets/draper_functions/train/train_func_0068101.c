t_warning(const char *str, ...)
{
    va_list ap;
    COL("43;01"); printf("WARNING:"); NOCOL;
    putchar(' ');
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap);
    warnings++;
    warned++;
    putchar('\n');
}
