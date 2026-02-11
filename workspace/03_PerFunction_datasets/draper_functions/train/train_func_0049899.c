QualityFromFormat(char *s)
{
    char *p, *q;
    char buf[200];
    int len;

    p = (char *)strstr(s, "quality");
    if (!p)
		return 0;
    p = (char *)strstr(p, "=");
    if (!p)
		return 0;
    p++;
    for (q=p; *q && isspace(*q); q++);
    for (p=q, len=0; *q && !isspace(*q); q++, len++);
    len++;
    if (len>=200)
		return 0;
    strncpy(buf, p, len);
    buf[len] = '\0';
    return (float)atoi(buf);
}
