ne_strdup(const char *s)
{
    char *ret;
    DO_MALLOC(ret, strlen(s) + 1);
    return strcpy(ret, s);
}
