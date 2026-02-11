heap_newstring(const char *s, const char *file, const int line)
{
    char *t;

    if (!s) return NULL;
    t = malloc((strlen(s) + 1) * sizeof(*t));
    if (!t) fatal3("out of memory", file, line);
    strcpy(t, s);
    return t;
}
