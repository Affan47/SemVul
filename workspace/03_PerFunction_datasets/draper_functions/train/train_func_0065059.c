hisv6_dispose(struct hisv6 *h)
{
    bool r;

    r = hisv6_closefiles(h);
    if (h->histpath) {
	free(h->histpath);
	h->histpath = NULL;
    }

    free(h);
    return r;
}
