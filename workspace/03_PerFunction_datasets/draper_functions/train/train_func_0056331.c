ns_desc_hop(_ns_hop * h, char *doc)
{
    if (!h) {
        D_ESCREEN(("%s: ns_desc_hop called with broken pointer!\n", doc ? doc : ""));
        return;
    }

    if (doc)
        D_ESCREEN(("%s:\n", doc));

    D_ESCREEN(("tunnel from localhost:%d to %s:%d to %s:%d is %s.  (delay %d, %d ref%s)\n",
               h->localport, h->fw, h->fwport, h->sess->host, h->sess->port, h->established ? "up" : "down", h->delay, h->refcount,
               h->refcount == 1 ? "" : "s"));
}
