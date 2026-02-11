safe_strsignal(int n)
{
    static char buffer[16];
    const char *s = strsignal(n);
    if (s && *s)
        return s;
    snprintf(buffer, sizeof(buffer), "signal %d", n);
    return buffer;
}
