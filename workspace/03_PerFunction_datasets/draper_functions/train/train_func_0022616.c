ParentSection(Widget w, XEvent *e, String *args, Cardinal *num)
#else
static void ParentSection(w, e, args, num)
Widget w;
XEvent *e;
String *args;
Cardinal *num;
#endif
{
    XmtHelpBrowserWidget hb = GetHelpBrowserAncestor(w);
    int nodenum = hb->help_browser.current_node_number;
    XmtHelpTree *parent = hb->help_browser.toc[nodenum]->parent;

    if (hb->help_browser.current_node_number <= 0)
	XBell(XtDisplay(w), 0);
    else {
	SetNode(hb, parent);
    }
}
