gdl_dock_item_constructor (GType                  type,
                           guint                  n_construct_properties,
                           GObjectConstructParam *construct_param)
{
    GObject *g_object;

    g_object = GDL_CALL_PARENT_WITH_DEFAULT (G_OBJECT_CLASS,
                                               constructor,
                                               (type,
                                                n_construct_properties,
                                                construct_param),
                                               NULL);
    if (g_object) {
        GdlDockItem *item = GDL_DOCK_ITEM (g_object);

        if (GDL_DOCK_ITEM_HAS_GRIP (item)) {
            item->_priv->grip_shown = TRUE;
            item->_priv->grip = gdl_dock_item_grip_new (item);
            gtk_widget_set_parent (item->_priv->grip, GTK_WIDGET (item));
            gtk_widget_show (item->_priv->grip);
        }
        else {
            item->_priv->grip_shown = FALSE;
        }
    }

    return g_object;
}
