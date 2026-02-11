UndoError(Widget text, XtPointer tag, XtPointer data)
#else
static void UndoError(text, tag, data)
Widget text;
XtPointer tag;
XtPointer data;
#endif
{
    XmtInputFieldWidget iw = (XmtInputFieldWidget) text;


    if (!iw->input_field.error_state) return;


    XtRemoveCallback(text, XmNvalueChangedCallback, UndoError, NULL);
    XtRemoveCallback(text, XmNfocusCallback, UndoError, NULL);
    XtRemoveCallback(text, XmNactivateCallback, UndoError, NULL);


    if (iw->input_field.error_string) {
	if (iw->input_field.replace_on_error) {
	    RestoreOldValue(iw);
	}
       	else {
	    SetString(text, iw->input_field.error_value);
	    XmTextSetInsertionPosition(text, XmTextGetLastPosition(text));
	    XtFree(iw->input_field.error_value);
	}
    }
    else if (iw->input_field.highlight_on_error) {

	if (((iw->input_field.error_background != (Pixel)-1) ||
	     (iw->input_field.error_foreground != (Pixel)-1)) &&
	    (iw->core.depth > 1)) {
	    Arg al[2];
	    int ac = 0;
	    if (iw->input_field.error_background != (Pixel)-1) {
		XtSetArg(al[ac],XmNbackground,iw->input_field.background);
		ac++;
	    }
	    if (iw->input_field.error_foreground != (Pixel)-1) {
		XtSetArg(al[ac],XmNforeground,iw->input_field.foreground);
		ac++;
	    }
	    XtSetValues(text, al, ac);
	}
	else {
	    XmTextSetHighlight(text, 0,XmTextGetLastPosition(text),
			       XmHIGHLIGHT_NORMAL);
	}

	if (iw->input_field.replace_on_error)
	    RestoreOldValue(iw);
    }

    iw->input_field.error_state = False;
}
