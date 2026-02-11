lookup_backend(const struct Backend_head *head, const char *hostname) {
    struct Backend *iter;

    if (hostname == NULL)
        hostname = "";

    STAILQ_FOREACH(iter, head, entries) {
        if (pcre_exec(iter->hostname_re, NULL, hostname, strlen(hostname), 0, 0, NULL, 0) >= 0) {
            syslog(LOG_DEBUG, "%s matched %s", iter->hostname, hostname);
            return iter;
        } else {
            syslog(LOG_DEBUG, "%s didn't match %s", iter->hostname, hostname);
        }
    }
    return NULL;
}
