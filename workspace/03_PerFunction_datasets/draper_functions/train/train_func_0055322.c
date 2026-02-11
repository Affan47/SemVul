ne_strndup(const char *s, size_t n)
{
    char *new;
    DO_MALLOC(new, n+1);
    new[n] = '\0';
    memcpy(new, s, n);
    return new;
}
