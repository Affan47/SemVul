gdl_dock_object_reorder (GdlDockObject    *object,
                         GdlDockObject    *child,
                         GdlDockPlacement  new_position,
                         GValue           *other_data)
{
    g_return_val_if_fail (object != NULL && child != NULL, FALSE);

    return GDL_CALL_VIRTUAL_WITH_DEFAULT (object,
                                          GDL_DOCK_OBJECT_GET_CLASS,
                                          reorder,
                                          (object, child, new_position, other_data),
                                          FALSE);
}
