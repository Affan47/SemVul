parse_listen(char *listen)
{
    char *cp;
    char *port = NULL;

    if ((cp = strrchr(listen,']')) != NULL) {

        if (*cp++ != '\0' && *cp == ':') {
            *cp++ = '\0';
            if (*cp != '\0') {
                port = cp;
            }
        }
    } else if ((cp = strrchr(listen,':')) != NULL) {

        *cp++ = '\0';
        if (*cp != '\0') {
            port = cp;
        }
    }
    return port;
}
