MoveCursorTimerProc(data, id)
XtPointer data;
XtIntervalId *id;
#endif
{
    XmtInputFieldWidget iw = (XmtInputFieldWidget)data;

    if (iw->input_field.pattern_skip != 0) {
	XmTextSetInsertionPosition((Widget)iw,
				   XmTextGetInsertionPosition((Widget)iw) +
				   iw->input_field.pattern_skip);
	iw->input_field.pattern_skip = 0;
    }
}
