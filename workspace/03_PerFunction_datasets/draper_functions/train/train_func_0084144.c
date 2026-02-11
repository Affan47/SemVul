VerifyCursorMotion(Widget w, XtPointer tag, XtPointer call_data)
#else
static void VerifyCursorMotion(w, tag, call_data)
Widget w;
XtPointer tag, call_data;
#endif
{
    XmtMsgLineWidget mw = (XmtMsgLineWidget) w;
    XmTextVerifyCallbackStruct *data = (XmTextVerifyCallbackStruct *)call_data;


    if (mw->msgline.permissive) return;

    if (data->newInsert < mw->msgline.inputpos) {
        data->doit = FALSE;
	XmTextSetInsertionPosition(w, mw->msgline.inputpos);
    }
}
