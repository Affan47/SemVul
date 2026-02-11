gdl_dock_object_reduce (GdlDockObject *object)
{
    g_return_if_fail (object != NULL);

    if (gdl_dock_object_is_frozen (object)) {
        object->priv->reduce_pending = TRUE;
        return;
    }

    if (GDL_DOCK_OBJECT_GET_CLASS (object)->reduce)
        GDL_DOCK_OBJECT_GET_CLASS (object)->reduce (object);
}
