gdl_dock_object_update_parent_visibility (GdlDockObject *object)
{
    GdlDockObject *parent;

    g_return_if_fail (object != NULL);

    parent = gdl_dock_object_get_parent_object (object);
    if (parent && gdl_dock_object_is_automatic (parent))
    {
        gboolean visible = FALSE;

        gtk_container_foreach (GTK_CONTAINER (parent),
                               (GtkCallback) gdl_dock_object_foreach_is_visible,
                               &visible);
        parent->priv->attached = visible;
#ifndef GDL_DISABLE_DEPRECATED
        if (visible)
            parent->deprecated_flags |= GDL_DOCK_ATTACHED;
        else
            parent->deprecated_flags &= ~GDL_DOCK_ATTACHED;
#endif
        gtk_widget_set_visible (GTK_WIDGET (parent), visible);
    }
    gdl_dock_object_layout_changed_notify (object);
}
