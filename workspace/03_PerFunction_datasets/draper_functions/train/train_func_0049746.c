gdl_dock_forall (GtkContainer *container,
                 gboolean      include_internals,
                 GtkCallback   callback,
                 gpointer      callback_data)
{
    GdlDock *dock;

    g_return_if_fail (container != NULL);
    g_return_if_fail (GDL_IS_DOCK (container));
    g_return_if_fail (callback != NULL);

    dock = GDL_DOCK (container);

    if (dock->priv->root)
        (*callback) (GTK_WIDGET (dock->priv->root), callback_data);
}
