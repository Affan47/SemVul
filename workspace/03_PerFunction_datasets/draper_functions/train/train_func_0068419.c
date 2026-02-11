xio_close_win(struct xio_win *xw, int dpy_too)
{
    struct xio *xio = xw->xio;

    XDestroyWindow(xio->dpy, xw->win);
    dl_remove(xw->node);
    free(xw);

    if (dpy_too && dl_empty(xio->windows))
	xio_close_dpy(xio);
}
