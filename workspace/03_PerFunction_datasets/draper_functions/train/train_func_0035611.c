strip(char *buf) {
    char *pch = buf + strlen(buf) - 1;
    while (pch > buf && isspace(*pch))
        *pch-- = '\0';

    while (isspace(*buf))
        buf++;

    return buf;
}
