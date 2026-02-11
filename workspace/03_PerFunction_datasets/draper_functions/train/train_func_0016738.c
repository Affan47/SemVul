HTTP_HeaderLineExists(char *cpBuf, char *name)
{
    char *cp1;
    char *cp2;
    char *cp2a;
    char *cp3;
    int n;

    n = strlen(name);
    cp2 = NULL;
    if ((cp2a = strstr(cpBuf, "\n\n")) != NULL)
        cp2 = cp2a;
    if ((cp2a = strstr(cpBuf, "\r\n\r\n")) != NULL && (cp2 == NULL || cp2a < cp2))
        cp2 = cp2a;
    if (cp2 != NULL) {
        for (cp1 = cpBuf; cp1 < cp2-1; ) {
            cp3 = strchr(cp1, '\n');
            if (HTTP_IsHeaderLine(cp1, cp3) && cp3-cp1 > n+1)
                if (strncasecmp(cp1, name, n) == 0)
                    return 1;
            cp1 = cp3+1;
        }
        return 0;
    }
    return 0;
}
