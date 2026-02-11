str_delete(char *s, const char *target)
{
    char *p;
    int n;
    if (s == NULL || target == NULL || *target == '\0') return;

    n = strlen(target);
    p = s;
    while ((p = strstr(p,target)))
        p = my_strcpy(p,p+n);
}
