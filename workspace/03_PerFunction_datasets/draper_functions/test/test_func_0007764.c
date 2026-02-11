Destroy(Widget gw)
{
    FileSelWidget	w = (FileSelWidget)gw;
    Display		*disp = XtDisplay(w);
    int			i;

    for (i = 0 ; i <= MAX_FILE_TYPE ; i++)
	XFreePixmap(disp, w->filesel.pixmap[i]);
    XtFree((char *)w->filesel.types);
}
