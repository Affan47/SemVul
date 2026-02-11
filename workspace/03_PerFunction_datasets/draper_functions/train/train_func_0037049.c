HelpCallback(Widget w, XtPointer tag, XtPointer data)
#else
static void HelpCallback(w, tag, data)
Widget w;
XtPointer tag, data;
#endif
{
    MsgDialogCache *cache = (MsgDialogCache *)tag;
    Widget dialog = XtParent(w);
    XmString msg, help, blank, s1, s2;
    int i;


    for(i=0; i < cache->num-1; i++)
	if (cache->dialogs[i] == dialog) break;

    XtVaGetValues(dialog, XmNmessageString, &msg, NULL);
    blank = XmStringSeparatorCreate();
    help = XmtCreateLocalizedXmString(w, cache->help_strings[i]);
    s1 = XmStringConcat(msg, blank);
    s2 = XmStringConcat(s1, help);
    XtVaSetValues(dialog, XmNmessageString, s2, NULL);
    XmStringFree(msg);
    XmStringFree(blank);
    XmStringFree(help);
    XmStringFree(s1);
    XmStringFree(s2);
    XtSetSensitive(w, False);
}
