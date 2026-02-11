x11_cursor(int mode)
{


    switch (mode) {
    case NORMALMOUSE:
	XDefineCursor(d->display, d->window, normal);

	break;
    case WAITMOUSE:
	XDefineCursor(d->display, d->window, xwait);

	break;
    case REPLAYMOUSE:
	XDefineCursor(d->display, d->window, replay);

	break;
    }
    XFlush(d->display);
}
