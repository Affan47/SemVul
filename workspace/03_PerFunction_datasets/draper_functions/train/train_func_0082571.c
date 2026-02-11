snmp_getpassphrase(const char *prompt, int bvisible)
{
    int             ti = 0;
    size_t          len;

    char           *bufp = NULL;
    static char     buffer[SNMP_MAXBUF];

    FILE           *ofp = stdout;


#ifdef HAVE_GETPASS
    if (isatty(0)) {
        return getpass((prompt) ? prompt : "");
    }
#endif

    fputs((prompt) ? prompt : "", ofp);

    if (!bvisible) {
        ti = snmp_ttyecho(0, 0);
    }

    bufp = fgets(buffer, sizeof(buffer), stdin);

    if (!bvisible) {
        ti = snmp_ttyecho(0, ti);
        fputs("\n", ofp);
    }
    if (!bufp) {
        fprintf(stderr, "Aborted...\n");
        exit(1);
    }


    len = strlen(buffer);
    if (buffer[len - 1] == '\n')
        buffer[--len] = '\0';

    bufp = (char *) calloc(1, len + 1);
    if (bufp)
        memcpy(bufp, buffer, len + 1);

    memset(buffer, 0, SNMP_MAXBUF);


    return bufp;

}
