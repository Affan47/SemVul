Down (Widget w, XEvent *ev, String *params, Cardinal *num_params)
{
  XlwMenuWidget mw = (XlwMenuWidget) w;
  widget_value* selected_item = mw->menu.old_stack [mw->menu.old_depth - 1];
  int popup_menu_p = mw->menu.top_depth == 1;


  if (mw->menu.old_depth == mw->menu.top_depth)


    set_new_state (mw,
                   find_first_selectable (mw,
                                          selected_item->contents,
                                          popup_menu_p),
                   mw->menu.old_depth);
  else

    set_new_state (mw, find_next_selectable (mw, selected_item, popup_menu_p),
                   mw->menu.old_depth - 1);

  remap_menubar (mw);
}
