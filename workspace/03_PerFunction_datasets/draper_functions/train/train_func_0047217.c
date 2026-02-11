parse_trapd_address(const char *token, char *cptr)
{
    char buf[BUFSIZ];
    char *p;
    cptr = copy_nword(cptr, buf, sizeof(buf));

    if (default_port == ddefault_port) {
        default_port = strdup(buf);
    } else {
        p = malloc(strlen(buf) + 1 + strlen(default_port) + 1);
        if (p) {
            strcat(p, buf);
            strcat(p, ",");
            strcat(p, default_port );
        }
        free(default_port);
        default_port = p;
    }
}
