XmtChooserSetSensitive(Widget w, int n, XmtWideBoolean sensitive)
#else
void XmtChooserSetSensitive(w, n, sensitive)
Widget w;
int n;
int sensitive;
#endif
{
    XmtChooserWidget cw = (XmtChooserWidget)w;

    XmtAssertWidgetClass(w, xmtChooserWidgetClass,"XmtChooserSetSensitive");

    if ((n < 0) || (n > cw->chooser.num_items)) {
	BoundsWarning(cw, n);
	return;
    }

    if (n > 31) {
	XmtWarningMsg("XmtChooserSetSensitive", "size",
		      "can only set sensitivity on first 32 items.");
	return;
    }


    if (cw->chooser.item_widgets)
	XtSetSensitive(cw->chooser.item_widgets[n], sensitive);


    if (sensitive)
	cw->chooser.insensitive &= ~(1 << n);
    else
	cw->chooser.insensitive |= 1 << n;
}
