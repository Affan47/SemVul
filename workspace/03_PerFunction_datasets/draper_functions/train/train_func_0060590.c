_gdl_dock_foreach_build_list (GdlDockObject *object,
                              gpointer       user_data)
{
    GList **l = (GList **) user_data;

    if (GDL_IS_DOCK_ITEM (object))
        *l = g_list_prepend (*l, object);
}
