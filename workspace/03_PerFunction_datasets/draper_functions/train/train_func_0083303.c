gdm_client_get_chooser_finish (GdmClient       *client,
                               GAsyncResult    *result,
                               GError         **error)
{
        GdmChooser *chooser;

        g_return_val_if_fail (GDM_IS_CLIENT (client), FALSE);

        if (client->priv->chooser != NULL) {
                return g_object_ref (client->priv->chooser);
        } else if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result),
                                                          error)) {
                return NULL;
        }

        chooser = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));

        client->priv->chooser = chooser;

        g_object_add_weak_pointer (G_OBJECT (client->priv->chooser),
                                   (gpointer *)
                                   &client->priv->chooser);

        g_object_weak_ref (G_OBJECT (client->priv->chooser),
                           (GWeakNotify)
                           g_object_unref,
                           client->priv->connection);

        g_object_weak_ref (G_OBJECT (client->priv->chooser),
                           (GWeakNotify)
                           g_clear_object,
                           &client->priv->manager);

        return g_object_ref (chooser);
}
