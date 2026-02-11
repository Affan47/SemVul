gdl_dock_get_placeholder_by_name (GdlDock     *dock,
                                  const gchar *name)
{
    GdlDockObject *found;

    g_return_val_if_fail (dock != NULL && name != NULL, NULL);


    found = gdl_dock_master_get_object (GDL_DOCK_OBJECT_GET_MASTER (dock), name);

    return (found && GDL_IS_DOCK_PLACEHOLDER (found)) ?
        GDL_DOCK_PLACEHOLDER (found) : NULL;
}
