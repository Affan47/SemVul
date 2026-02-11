gdl_dock_item_hide_cb (GtkWidget   *widget,
                       GdlDockItem *item)
{
    g_return_if_fail (item != NULL);

    gdl_dock_item_hide_item (item);
}
