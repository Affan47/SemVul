gdl_dock_object_present (GdlDockObject *object,
                         GdlDockObject *child)
{
    GdlDockObject *parent;

    g_return_if_fail (object != NULL && GDL_IS_DOCK_OBJECT (object));

    parent = gdl_dock_object_get_parent_object (object);
    if (parent)

        gdl_dock_object_present (parent, object);

   if (GDL_DOCK_OBJECT_GET_CLASS (object)->present)
        GDL_DOCK_OBJECT_GET_CLASS (object)->present (object, child);
}
