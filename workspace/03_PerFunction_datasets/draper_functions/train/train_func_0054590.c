display_welcome (MenuItems *menuitems)
{
  GooCanvasItem *item;
  RsvgHandle  *svg_handle;

  if (actualSectionItem)
    g_error("actualSectionItem exists in display_section !");


  actualSectionItem = goo_canvas_group_new(boardRootItem,
					   NULL);

  svg_handle = gc_skin_rsvg_get();
  item = goo_canvas_svg_new (actualSectionItem,
			     svg_handle,
			     "svg-id", "#LOGO",
			     NULL);
  SET_ITEM_LOCATION_CENTER(item,
			   display_x + display_w/2.0,
			   display_y + display_h/3.0);

  display_sponsor(actualSectionItem);

  g_signal_connect (item, "enter_notify_event",
		    (GCallback) display_welcome_event, menuitems);
  g_signal_connect (item, "leave_notify_event",
		    (GCallback) on_leave_notify, menuitems);

  menu_displayed = TRUE;
}
