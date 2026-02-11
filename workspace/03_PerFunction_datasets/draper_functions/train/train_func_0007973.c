numset(char *s, size_t len, long n)
{
    snprintf(s, len, "%ld", n);
    while (len > 0 && *s)
    {
        ++s;
        --len;
    }
    while (len > 0)
    {
        *s++ = ' ';
        --len;
    }
}
