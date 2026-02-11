XmtAddSaveYourselfCallback(Widget shell,
				XtCallbackProc proc, XtPointer data)
#else
void XmtAddSaveYourselfCallback(shell, proc, data)
Widget shell;
XtCallbackProc proc;
XtPointer data;
#endif
{
    static Atom wm_save_yourself;

    if (!XtIsApplicationShell(shell)) {
	XmtWarningMsg("XmtAddSaveYourselfCallback", "badShell",
		      "specified shell '%s' is not an ApplicationShell.",
		      XtName(shell));
	return;
    }

    if (!wm_save_yourself) {
	wm_save_yourself = XmInternAtom(XtDisplay(shell),
					"WM_SAVE_YOURSELF", False);
    }
    else {
	XmtWarningMsg("XmtAddSaveYourselfCallback", "multiple",
		      "only one callback may be registered per process.");
	return;
    }

    XmAddWMProtocolCallback(shell, wm_save_yourself, proc, data);
}
