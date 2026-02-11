compute_v4_addr(interface_defn * ifd UNUSED, char **pparam, int argc UNUSED, char **argv UNUSED)
{
    char s[INET_ADDRSTRLEN * 2 + 2];
    strncpy(s, *pparam, sizeof(s));
    s[sizeof(s) - 1] = 0;

    char *token = strtok(s, "/");
    if (!token)
        return;

    *pparam = realloc(*pparam, strlen(token) + 1);
    if (*pparam == NULL)
        return;
    strcpy(*pparam, token);
}
