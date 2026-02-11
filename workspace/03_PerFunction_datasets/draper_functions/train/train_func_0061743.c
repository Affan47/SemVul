CopyString(const char *s)
{
    int len;
    char *s2;

    len = strlen(s)-2;
    if (!(s2 = malloc(len+1)))
	Die("No memory\n");
    strncpy(s2, s+1, len);
    s2[len] = '\0';
    return s2;
}
