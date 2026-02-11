child_std_open(
    struct child_std *cs,
    struct error_buffer *errbuf) {

    cs->path = strdup(cs->template);
    if (cs->path == NULL) {
        strncpy(errbuf->s, "strdup() failed", errbuf->n);
        return -1;
    }

    cs->fd = mkostemp(cs->path, O_WRONLY | O_CLOEXEC);
    if (cs->fd < 0) {
        snprintf(errbuf->s, errbuf->n, "mkstemp() failed for %s, %s",
            cs->template, strerror(errno));
        return -1;
    }

    if (fchmod(cs->fd, S_IRUSR) < 0) {
        snprintf(errbuf->s, errbuf->n, "fchmod() failed for %s, %s",
            cs->path, strerror(errno));
        return -1;
    }

    return 0;
}
