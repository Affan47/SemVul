xlw_popup_menu (widget, event)
     Widget widget;
     XEvent *event;
{
  XlwMenuWidget mw;

  if (!XtIsShell (widget))
    return;

  mw = (XlwMenuWidget)((CompositeWidget)widget)->composite.children [0];

  if (event)
    XtCallActionProc ((Widget) mw, "start", event, NULL, 0);
  else
    {
      XEvent dummy;
      XButtonPressedEvent *bd = &dummy.xbutton;

      bd->type = ButtonPress;
      bd->serial = 0;
      bd->send_event = 0;
      bd->display = XtDisplay (widget);
      bd->window = XtWindow (XtParent (widget));
      bd->time = CurrentTime;
      bd->button = 0;
      XQueryPointer (bd->display, bd->window, &bd->root,
		     &bd->subwindow, &bd->x_root, &bd->y_root,
		     &bd->x, &bd->y, &bd->state);

      XtCallActionProc ((Widget) mw, "start", &dummy, NULL, 0);
    }
}
