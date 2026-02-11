xfer_done(struct xfer_header **xferptr)
{
    struct xfer_header *xfer = *xferptr;
    struct xfer_item *item, *next;


    item = xfer->items;
    while (item) {
	next = item->next;
	free(item->name);
	free(item->part);
	free(item->acl);
	free(item);
	item = next;
    }


    if (xfer->mupdate_h) mupdate_disconnect(&xfer->mupdate_h);
    if (xfer->be) backend_disconnect(xfer->be);
    free(xfer->toserver);
    free(xfer->topart);

    seen_close(&xfer->seendb);

    free(xfer);

    *xferptr = NULL;
}
