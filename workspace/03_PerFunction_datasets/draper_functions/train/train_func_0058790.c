sprintf(const char* fmt, ...)
{
    int r;
    va_list ap;
    va_start(ap, fmt);

#ifdef _GNU_SOURCE
    char* s = 0;
    r = vasprintf(&s, fmt, ap);
#else


    char s[1000];
    r = vsnprintf(s, sizeof(s), fmt, ap);
#endif

    va_end(ap);

    if (s && r > 0)
    {
	string tmp(s, r);
	swap(tmp);
    }
    else
    {
	string tmp;
	swap(tmp);
	r = 0;
    }

#ifdef _GNU_SOURCE
    free(s);
#endif

    return r;
}
