gdl_dock_notebook_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
    GdlDockItem *item = GDL_DOCK_ITEM (object);

    switch (prop_id) {
        case PROP_PAGE:
            if (item->child && GTK_IS_NOTEBOOK (item->child)) {
                g_value_set_int (value, gtk_notebook_get_current_page
                                 (GTK_NOTEBOOK (item->child)));
            }

            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
