build_pax_attribute_name(char *dest, const char *src)
{
    char buff[64];
    const char *p;


    if (src == NULL || *src == '\0') {
        strcpy(dest, "PaxHeader/blank");
        return (dest);
    }


    p = src + strlen(src);
    for (;;) {

        if (p > src && p[-1] == '/') {
            --p;
            continue;
        }

        if (p > src + 1 && p[-1] == '.'
            && p[-2] == '/') {
            --p;
            continue;
        }
        break;
    }


    if (p == src) {
        strcpy(dest, "/PaxHeader/rootdir");
        return (dest);
    }


    if (*src == '.' && p == src + 1) {
        strcpy(dest, "PaxHeader/currentdir");
        return (dest);
    }


#if HAVE_GETPID && 0
    sprintf(buff, "PaxHeader.%d", getpid());
#else

    strcpy(buff, "PaxHeader");
#endif

    build_ustar_entry_name(dest, src, p - src, buff);

    return (dest);
}
