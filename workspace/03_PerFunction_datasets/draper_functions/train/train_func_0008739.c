got_introspection (GUPnPServiceInfo          *info,
                   GUPnPServiceIntrospection *introspection,
                   const GError              *error,
                   gpointer                   user_data)
{
        GtkTreeModel *model;
        GtkTreeIter  *service_iter;

        service_iter = (GtkTreeIter *) user_data;

        model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
        g_assert (model != NULL);

        append_introspection (GUPNP_SERVICE_PROXY (info),
                              introspection,
                              GTK_TREE_STORE (model),
                              service_iter);

        g_slice_free (GtkTreeIter, service_iter);
        if (introspection != NULL) {
                g_object_unref (introspection);


                gupnp_service_proxy_set_subscribed (GUPNP_SERVICE_PROXY (info), TRUE);
        }
}
