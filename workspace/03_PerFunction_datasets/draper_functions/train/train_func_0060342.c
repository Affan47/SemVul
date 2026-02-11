garcon_gtk_menu_item_drag_begin (GarconMenuItem *item,
                                 GdkDragContext *drag_context)
{
  const gchar *icon_name;

  g_return_if_fail (GARCON_IS_MENU_ITEM (item));

  icon_name = garcon_menu_item_get_icon_name (item);
  if (!STR_IS_EMPTY (icon_name))
    gtk_drag_set_icon_name (drag_context, icon_name, 0, 0);
}
