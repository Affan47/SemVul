dpy2dri(Display *dpy)
{
	DRI2Display *dri2dpy;
	list_for_each_entry(dri2dpy, &dpy_list, list) {
		if (dri2dpy->dpy == dpy) {
			return dri2dpy;
		}
	}
	return NULL;
}
