CvtStringToLabelPosition(dpy, args, num_args, from, to, data)
Display *dpy;
XrmValuePtr args;
Cardinal *num_args;
XrmValuePtr from, to;
XtPointer *data;
{
    static XbaeLabelPosition position;

    if (*num_args != 0)
        XtAppWarningMsg(
            XtDisplayToApplicationContext(dpy),
            "cvtStringToLabelPosition", "wrongParameters",
            "XbaeCaption",
            "String to LabelPosition conversion needs no extra arguments",
            NULL, NULL);


    if (to->addr != NULL && to->size < sizeof(XbaeLabelPosition)) {
        to->size = sizeof(XbaeLabelPosition);
        return False;
    }

    if (CompareStrings(from->addr, "left"))
        position = XbaePositionLeft;
    else if (CompareStrings(from->addr, "right"))
        position = XbaePositionRight;
    else if (CompareStrings(from->addr, "top"))
        position = XbaePositionTop;
    else if (CompareStrings(from->addr, "bottom"))
        position = XbaePositionBottom;
    else {
        XtDisplayStringConversionWarning(dpy, from->addr, XmRLabelPosition);
        return False;
    }


    if (to->addr == NULL)
        to->addr = (XtPointer) &position;
    else
        *(XbaeLabelPosition *) to->addr = position;
    to->size = sizeof(XbaeLabelPosition);

    return True;
}
