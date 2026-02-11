gdl_dock_item_grip_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
    GdlDockItemGrip *grip;

    g_return_if_fail (GDL_IS_DOCK_ITEM_GRIP (object));

    grip = GDL_DOCK_ITEM_GRIP (object);

    switch (prop_id) {
        case PROP_ITEM:
            grip->item = g_value_get_object (value);
            if (grip->item) {
                g_signal_connect (grip->item, "notify::long_name",
                                  G_CALLBACK (gdl_dock_item_grip_item_notify),
                                  grip);
                g_signal_connect (grip->item, "notify::stock_id",
                                  G_CALLBACK (gdl_dock_item_grip_item_notify),
                                  grip);
		g_signal_connect (grip->item, "notify::behavior",
		                  G_CALLBACK (gdl_dock_item_grip_item_notify),
				  grip);

                if (!GDL_DOCK_ITEM_CANT_CLOSE (grip->item) && grip->_priv->close_button)
                    gtk_widget_show (grip->_priv->close_button);
                if (!GDL_DOCK_ITEM_CANT_ICONIFY (grip->item) && grip->_priv->iconify_button)
                    gtk_widget_show (grip->_priv->iconify_button);
            }
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
