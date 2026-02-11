Select (w, ev, params, num_params)
     Widget w;
     XEvent *ev;
     String *params;
     Cardinal *num_params;
{
  XlwMenuWidget mw = (XlwMenuWidget)w;
  widget_value* selected_item = mw->menu.old_stack [mw->menu.old_depth - 1];


  if ((selected_item == 0
       || ((widget_value *) selected_item)->call_data == 0)
      && !next_release_must_exit
      && (ev->xbutton.time - menu_post_event.xbutton.time
	  < XtGetMultiClickTime (XtDisplay (w))))
    return;


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
	  display_menu (mw, 0, False, NULL, NULL, NULL, NULL, NULL);
	}
    }


  XtCallCallbackList ((Widget)mw, mw->menu.select, (XtPointer)selected_item);
}
