XmtGetVisual(Widget w)
#else
Visual *XmtGetVisual(w)
Widget w;
#endif
{
    while(!XtIsShell(w)) w = XtParent(w);
    if (((ShellWidget)w)->shell.visual != (Visual *)CopyFromParent)
	return ((ShellWidget)w)->shell.visual;
    else
	return DefaultVisualOfScreen(XtScreen(w));
}
