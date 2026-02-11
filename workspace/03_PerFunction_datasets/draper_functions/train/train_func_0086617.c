nerror(const char *fmt, ...)
{
    char	    *s1;
    va_list	    ap;
    int		    n;

    n = errno;
    va_start(ap, fmt);
    s1 = vmprintf_errok(fmt, ap);
    va_end(ap);
    if (!s1)
	double_jeopardy();
    s1 = copy_string(s1);
    if (n == ENOMEM)
	resource_usage_print();
    error_raw("%s: %s", s1, strerror(n));
    free(s1);
}
