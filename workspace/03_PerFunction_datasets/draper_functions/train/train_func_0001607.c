edwin_new(struct xio *xio, struct vbi *vbi, int pgno, int subno)
{
    struct edwin *w;
    struct vt_page *vtp;
    u8 buf[64];
    int i;

    if (not(w = malloc(sizeof(*w))))
	goto fail1;

    if (not(w->xw = xio_open_win(xio, 0)))
	goto fail2;

    w->pgno = pgno;
    w->subno = subno;

    vtp = vbi_query_page(vbi, pgno, subno);
    if (vtp)
	for (i = 0; i < 25; ++i)
	    xio_put_line(w->xw, i, vtp->data[i]);
    else
	xio_clear_win(w->xw);

    w->mode = 1;
    w->edline = 0;
    if (w->subno == ANY_SUB)
	sprintf(buf, "Editor %03x", w->pgno);
    else
	sprintf(buf, "Editor %03x/%x", w->pgno, w->subno);
    xio_title(w->xw, buf);
    xio_set_concealed(w->xw, w->reveal = 1);
    xio_set_handler(w->xw, edwin_event, w);
    cursor(w, W/2, H/2);
    return w;

fail2:
    free(w);
fail1:
    return 0;
}
