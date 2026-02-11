XmtConvertStringToBitmap(Display *dpy,
				 XrmValue *args, Cardinal *num_args,
				 XrmValue *from, XrmValue *to,
				 XtPointer *data)
#else
Boolean XmtConvertStringToBitmap(dpy, args, num_args, from, to, data)
Display *dpy;
XrmValue *args;
Cardinal *num_args;
XrmValue *from;
XrmValue *to;
XtPointer *data;
#endif
{
    String str = from->addr;
    Pixmap bitmap;

    bitmap = XmtGetBitmap(*(Widget *)args[0].addr, str);
    if (!bitmap) {
	XtDisplayStringConversionWarning(dpy, str, XtRBitmap);
	return False;
    }
    done(Pixmap, bitmap)
}
