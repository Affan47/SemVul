is_feed(const char *mbox)
{
    static struct wildmat *feeds = NULL;
    struct wildmat *wild;

    if (!feeds) {
	feeds = split_wildmats((char *) config_getstring(IMAPOPT_RSS_FEEDS),
			       NULL);
    }


    wild = feeds;
    while (wild->pat && wildmat(mbox, wild->pat) != 1) wild++;


    if (!wild->pat || wild->not) return 0;


    return 1;
}
