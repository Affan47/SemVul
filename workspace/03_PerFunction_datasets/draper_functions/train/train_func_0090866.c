XmtChooserSetItemValue(Widget w, int item, XtPointer valuep)
#else
void XmtChooserSetItemValue(w, item, valuep)
Widget w;
int item;
XtPointer valuep;
#endif
{
    XmtChooserWidget cw = (XmtChooserWidget) w;
    XmtAssertWidgetClass(w, xmtChooserWidgetClass,"XmtChooserLookupItemValue");

    if ((item < 0) || (item > cw->chooser.num_items)) {
	BoundsWarning(cw, item);
	return;
    }

    if (!cw->chooser.values)
	cw->chooser.values = (XtPointer) XtCalloc(cw->chooser.num_items,
						  cw->chooser.value_size);

    memmove(&((char *)cw->chooser.values)[item * cw->chooser.value_size],
	    valuep,
	    cw->chooser.value_size);
}
