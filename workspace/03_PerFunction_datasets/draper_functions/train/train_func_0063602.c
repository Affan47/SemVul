gdl_dock_new_from (GdlDock  *original,
                   gboolean  floating)
{
    GObject *new_dock;

    g_return_val_if_fail (original != NULL, NULL);

    new_dock = g_object_new (GDL_TYPE_DOCK,
                             "master", GDL_DOCK_OBJECT_GET_MASTER (original),
                             "floating", floating,
                             NULL);
    GDL_DOCK_OBJECT_UNSET_FLAGS (new_dock, GDL_DOCK_AUTOMATIC);

    return GTK_WIDGET (new_dock);
}
