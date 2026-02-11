gdl_dock_tablabel_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
    GdlDockTablabel *tablabel;
    GtkBin          *bin;

    tablabel = GDL_DOCK_TABLABEL (object);

    switch (prop_id) {
        case PROP_ITEM:
            if (tablabel->item) {
                g_object_remove_weak_pointer (G_OBJECT (tablabel->item),
                                              (gpointer *) &tablabel->item);
                g_signal_handlers_disconnect_by_func (
                    tablabel->item, gdl_dock_tablabel_item_notify, tablabel);
            };

            tablabel->item = g_value_get_object (value);
            if (tablabel->item) {
                gboolean locked;
                gchar   *long_name;

                g_object_add_weak_pointer (G_OBJECT (tablabel->item),
                                           (gpointer *) &tablabel->item);

                g_signal_connect (tablabel->item, "notify::locked",
                                  G_CALLBACK (gdl_dock_tablabel_item_notify),
                                  tablabel);
                g_signal_connect (tablabel->item, "notify::long_name",
                                  G_CALLBACK (gdl_dock_tablabel_item_notify),
                                  tablabel);
                g_signal_connect (tablabel->item, "notify::grip_size",
                                  G_CALLBACK (gdl_dock_tablabel_item_notify),
                                  tablabel);

                g_object_get (tablabel->item,
                              "locked", &locked,
                              "long-name", &long_name,
                              "grip-size", &tablabel->drag_handle_size,
                              NULL);

                if (locked)
                    tablabel->drag_handle_size = 0;

                bin = GTK_BIN (tablabel);
                if (gtk_bin_get_child (bin) && g_object_class_find_property (
                    G_OBJECT_GET_CLASS (gtk_bin_get_child (bin)), "label"))
                    g_object_set (gtk_bin_get_child (bin), "label", long_name, NULL);
                g_free (long_name);
            };
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
