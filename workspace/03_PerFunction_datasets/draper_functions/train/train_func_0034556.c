xbaeCommitEditACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
    XbaeMatrixWidget mw;
    Boolean unmap;


    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
        mw = (XbaeMatrixWidget)w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
        mw = (XbaeMatrixWidget)XtParent(w);
    else
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext(w),
            "commitEditACT", "badWidget", "XbaeMatrix",
            "XbaeMatrix: Bad widget passed to CommitEdit action",
            NULL, 0);
        return;
    }


    if (*nparams != 1)
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext(w),
            "commitEditACT", "badParms", "XbaeMatrix",
            "XbaeMatrix: Wrong params for CommitEdit action, needs 1",
            NULL, 0);
        return;
    }


    if (!strcmp(params[0], "True"))
        unmap = True;
    else if (!strcmp(params[0], "False"))
        unmap = False;
    else
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext(w),
            "commitEditACT", "badParm", "XbaeMatrix",
            "XbaeMatrix: Bad parameter for CommitEdit action",
            NULL, 0);
        return;
    }

    (void)(*((XbaeMatrixWidgetClass)XtClass(mw))->matrix_class.commit_edit)
        (mw, event, unmap);
}
