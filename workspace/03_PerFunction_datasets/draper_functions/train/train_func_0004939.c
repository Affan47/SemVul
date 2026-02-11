xfer_user_cb(char *name,
			int matchlen __attribute__((unused)),
			int maycreate __attribute__((unused)),
			void *rock)
{
    struct xfer_header *xfer = (struct xfer_header *)rock;
    struct mboxlist_entry mbentry;
    int r;


    r = mboxlist_lookup(name, &mbentry, NULL);
    if (r) return r;


    if (mbentry.mbtype & MBTYPE_REMOTE) return 0;

    xfer_addmbox(xfer, name, &mbentry);

    return 0;
}
