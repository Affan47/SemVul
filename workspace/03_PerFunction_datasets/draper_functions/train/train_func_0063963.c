hisv6_unlink(struct hisv6 *h)
{
    bool r = true;
    char *p;

#ifdef DO_TAGGED_HASH
    p = concat(h->histpath, ".pag", NULL);
    r = (unlink(p) == 0) && r;
    free(p);
#else
    p = concat(h->histpath, ".index", NULL);
    r = (unlink(p) == 0) && r;
    free(p);

    p = concat(h->histpath, ".hash", NULL);
    r = (unlink(p) == 0) && r;
    free(p);
#endif

    p = concat(h->histpath, ".dir", NULL);
    r = (unlink(p) == 0) && r;
    free(p);

    r = (unlink(h->histpath) == 0) && r;
    return r;
}
