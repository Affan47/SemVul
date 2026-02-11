make_revstr(void)
{
    char *ptr;
    size_t len;
    ptr = strstr(rcs_revstr, ": ");
    if (!ptr) {
        revstr = strdup("unknown");
        return;
    }
    ptr += 2;

    minor_version = atoi(ptr);
    revstr = xmalloc(20);
    snprintf(revstr, 20, "%d.%d", major_version, minor_version);
}
