getcmaps(c)
Client *c;
{
	int n, i;
	Window *cw;
	XWindowAttributes attr;

	if (!c->init) {
		XGetWindowAttributes(dpy, c->window, &attr);
		c->cmap = attr.colormap;
	}

	n = _getprop(c->window, wm_colormaps, XA_WINDOW, 100L, (unsigned char **)&cw);
	if (c->ncmapwins != 0) {
		XFree((char *)c->cmapwins);
		free((char *)c->wmcmaps);
	}
	if (n <= 0) {
		c->ncmapwins = 0;
		return;
	}

	c->ncmapwins = n;
	c->cmapwins = cw;

	c->wmcmaps = (Colormap*)malloc(n*sizeof(Colormap));
	for (i = 0; i < n; i++) {
		if (cw[i] == c->window)
			c->wmcmaps[i] = c->cmap;
		else {
			XSelectInput(dpy, cw[i], ColormapChangeMask);
			XGetWindowAttributes(dpy, cw[i], &attr);
			c->wmcmaps[i] = attr.colormap;
		}
	}
}
