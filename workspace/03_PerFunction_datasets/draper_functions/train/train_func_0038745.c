gdl_dock_paned_constructor (GType                  type,
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

        if (!item->child)
            gdl_dock_paned_create_child (GDL_DOCK_PANED (g_object),
                                         item->orientation);


    }

    return g_object;
}
