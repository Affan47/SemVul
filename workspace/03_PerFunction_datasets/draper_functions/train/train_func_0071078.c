dispatch_flush(fbuf)
    fbuf_t *fbuf;
{
    int status = 0;

    if (fbuf->ocount) {
	status = do_flush(fbuf, fbuf->obuf, fbuf->ocount);
	fbuf->ocount = 0;
    }

    return (status);
}
