set_title(struct vtwin *w)
{
    char buf[32], buf2[32];

    if (w->subno == ANY_SUB)
	sprintf(buf, "%x", w->pgno);
    else
	sprintf(buf, "%x/%x", w->pgno, w->subno);
    if (w->searching)
	sprintf(buf2, "(%s)", buf);
    else
	sprintf(buf2, "%s", buf);
    xio_title(w->xw, buf2);
}
