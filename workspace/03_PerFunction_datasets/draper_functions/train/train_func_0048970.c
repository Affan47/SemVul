canvasBusy(w)
CanvasWidget w;
{
	XSetWindowAttributes attr;

	if ((attr.cursor = w->canvas.busy_cursor) != None) {
		XChangeWindowAttributes(XtDisplay(w), XtWindow(w),
					CWCursor, &attr);
		XFlush(XtDisplay(w));
	}
}
