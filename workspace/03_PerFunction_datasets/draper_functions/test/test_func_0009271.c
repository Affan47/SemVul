rss_parse_path(const char *path,
			  struct request_target_t *tgt,
			  const char **errstr __attribute__((unused)))
{
    const char *start, *end;
    size_t len;


    start = path + strlen("/rss");
    if (*start == '/') start++;
    end = start + strlen(start);

    if ((end > start) && (end[-1] == '/')) end--;

    len = end - start;
    if (len > MAX_MAILBOX_BUFFER) return IMAP_MAILBOX_BADNAME;

    strncpy(tgt->mboxname, start, len);
    tgt->mboxname[len] = '\0';

    mboxname_hiersep_tointernal(&httpd_namespace, tgt->mboxname, len);

    return 0;
}
