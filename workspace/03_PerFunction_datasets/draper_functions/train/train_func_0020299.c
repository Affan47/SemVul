gdl_dock_item_preferred_size (GdlDockItem    *item,
                              GtkRequisition *req)
{
    if (!req)
        return;

    req->width = MAX (item->_priv->preferred_width,
                      GTK_WIDGET (item)->allocation.width);
    req->height = MAX (item->_priv->preferred_height,
                       GTK_WIDGET (item)->allocation.height);
}
