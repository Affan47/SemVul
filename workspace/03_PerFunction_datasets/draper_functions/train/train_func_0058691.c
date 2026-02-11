gdl_dock_notebook_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
    GdlDockItem *item = GDL_DOCK_ITEM (object);
    GtkWidget *child;

    switch (prop_id) {
        case PROP_PAGE:
            child = gdl_dock_item_get_child (item);
            if (child && GTK_IS_NOTEBOOK (child)) {
                g_value_set_int (value, gtk_notebook_get_current_page
                                 (GTK_NOTEBOOK (child)));
            }

            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
