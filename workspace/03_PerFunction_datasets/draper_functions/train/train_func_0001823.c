getvalue(Widget w, XtPointer address, XrmQuark type, Cardinal size)
#else
static void getvalue(w, address, type, size)
Widget w;
XtPointer address;
XrmQuark type;
Cardinal size;
#endif
{
    if (type == XmtQString)
	*(String *)address = XmTextFieldGetString(w);
    else if (type == XmtQBuffer) {
	String s = XmTextFieldGetString(w);
	int len = strlen(s);

	strncpy(address, s, size-1);
	((char *)address)[size-1] = '\0';
	if (len >= size)
	    XmtWarningMsg("XmtDialogGetDialogValues", "xmtextfTrunc",
			  "The input value is %d characters long\n\tand does not fit into a buffer %d characters long.\n\tThe trailing characters have been truncated.",
			  len+1, size);
	XtFree(s);
    }
    else
	XmtWarningMsg("XmtDialogGetDialogValues", "xmtextfType",
		      "Type mismatch:\n\tCan't set input value on a resource of type '%s'.  String or Buffer expected.",
		      XrmQuarkToString(type));
}
