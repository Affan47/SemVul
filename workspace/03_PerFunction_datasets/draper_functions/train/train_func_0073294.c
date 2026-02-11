cvt_string_to_justify(Display *disp,
			      XrmValue *args, Cardinal *no_args,
			      XrmValue *from, XrmValue *to,
			      XtPointer *client_data)
{
    static JustifyType	just;
    static XrmQuark     left = 0, center, right;
    XrmQuark		q;
    char		*s = (char *)from->addr;
    char		buffer[32];

    if (!s || strlen(s) > 30)
	return False;

    if (!left) {
        left   = XrmPermStringToQuark("left");
        center = XrmPermStringToQuark("center");
        right  = XrmPermStringToQuark("right");
    }

    if (to->addr && to->size < sizeof just) {
	to->size = sizeof just;
	return False;
    }

    strcpy(buffer, s);
    ascii_lower(buffer);
    q = XrmStringToQuark(buffer);

    if (q == left)
	just = JustifyTypeLeft;
    else if (q == center)
	just = JustifyTypeCenter;
    else if (q == right)
	just = JustifyTypeRight;
    else {
	XtStringConversionWarning((char *)from->addr, XtRJustify);
	return False;
    }

    to->size = sizeof just;
    if (to->addr)
	*(JustifyType *)to->addr = just;
    else
	to->addr = (XPointer)&just;

    return True;
}
