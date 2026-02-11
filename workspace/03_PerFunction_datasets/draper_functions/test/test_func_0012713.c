gva_column_manager_set_managed_view (GvaColumnManager *manager,
                                     GtkTreeView *managed_view)
{
        g_return_if_fail (GVA_IS_COLUMN_MANAGER (manager));

        if (managed_view != NULL)
                g_return_if_fail (GTK_IS_TREE_VIEW (managed_view));

        if (manager->priv->managed_view != NULL)
        {
                g_signal_handlers_disconnect_by_func (
                        manager->priv->managed_view,
                        column_manager_update_view, manager);

                g_object_unref (manager->priv->managed_view);
                manager->priv->managed_view = NULL;
        }

        if (managed_view != NULL)
        {
                g_signal_connect_swapped (
                        managed_view, "columns-changed",
                        G_CALLBACK (column_manager_update_view), manager);

                manager->priv->managed_view = g_object_ref (managed_view);

                column_manager_update_view (manager);
        }
}
