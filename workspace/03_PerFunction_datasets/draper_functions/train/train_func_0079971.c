Infowin_set_name(const char *name)
{
	Status st;
	XTextProperty tp;
	char buf[128];
	char *bp = buf;
	my_strcpy(buf, name, sizeof(buf));
	st = XStringListToTextProperty(&bp, 1, &tp);
	if (st) XSetWMName(Metadpy->dpy, Infowin->win, &tp);
	return (0);
}
