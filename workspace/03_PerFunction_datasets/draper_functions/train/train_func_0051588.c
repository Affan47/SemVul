Key (Widget w, XEvent *ev, String *params, Cardinal *num_params)
{
  XlwMenuWidget mw = (XlwMenuWidget)w;


  mw->menu.new_depth = 1;
  remap_menubar (mw);

  if (mw->menu.popped_up)
    {
      mw->menu.popped_up = False;
      ungrab_all ((Widget)mw, ev->xmotion.time);
      if (XtIsShell (XtParent ((Widget) mw)))
	XtPopdown (XtParent ((Widget) mw));
      else
	{
	  XtRemoveGrab ((Widget) mw);
	  display_menu (mw, 0, False, NULL, NULL, NULL);
	}
    }


  XtCallCallbackList ((Widget)mw, mw->menu.select, (XtPointer)0);
}
