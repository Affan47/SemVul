set_umask(char *mask_string)
{
#ifndef WIN32
    int rc;
    unsigned mask;
    char *end;

    mask = strtoul(mask_string, &end, 8);
    if(!end || *end != '\0') {
        errno = EINVAL;
        return -1;
    }

    rc = umask(mask);
    return rc;
#else

    return 0;
#endif
}
