StoreCmap0(PLStream *pls)
{
    XwDev *dev = (XwDev *) pls->dev;
    XwDisplay *xwd = (XwDisplay *) dev->xwd;
    int i;

    if ( ! xwd->color)
	return;

    for (i = 1; i < xwd->ncol0; i++) {
	PLColor_to_XColor(&pls->cmap0[i], &xwd->cmap0[i]);
	if (xwd->rw_cmap)
	  XStoreColor(xwd->display, xwd->map, &xwd->cmap0[i]);
	else
	  XAllocColor( xwd->display, xwd->map, &xwd->cmap0[i]);
    }
}
