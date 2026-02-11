gdl_dock_item_iconify_item (GdlDockItem *item)
{
    g_return_if_fail (item != NULL);

    GDL_DOCK_OBJECT_SET_FLAGS (item, GDL_DOCK_ICONIFIED);
    gdl_dock_item_hide_item (item);
}
