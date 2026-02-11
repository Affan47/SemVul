Right (Widget w, XEvent *ev, String *params, Cardinal *num_params)
{
  XlwMenuWidget mw = (XlwMenuWidget) w;
  widget_value* selected_item = mw->menu.old_stack [mw->menu.old_depth - 1];


  if (mw->menu.old_depth == mw->menu.top_depth)


    set_new_state (mw, find_next_selectable (mw, selected_item, 0),
                   mw->menu.old_depth - 1);
  else if (selected_item->contents)
    {
      set_new_state (mw, selected_item->contents, mw->menu.old_depth);
      remap_menubar (mw);
      selected_item = mw->menu.old_stack [mw->menu.old_depth - 1];
      if (!selected_item->enabled && find_first_selectable (mw,
                                                            selected_item,
                                                            0))
	set_new_state (mw, find_first_selectable (mw, selected_item, 0),
                       mw->menu.old_depth - 1);
    }
  else
    {
      pop_new_stack_if_no_contents (mw);
      set_new_state (mw, mw->menu.old_stack [mw->menu.old_depth - 2],
                     mw->menu.old_depth - 2);
    }

  remap_menubar (mw);
}
