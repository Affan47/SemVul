create_contexts (gpointer data)
{
        GUPnPSimpleContextManager *manager = (GUPnPSimpleContextManager *) data;
        GList *ifaces;

        manager->priv->idle_context_creation_src = NULL;

        if (manager->priv->contexts != NULL)
               return FALSE;

        ifaces = gupnp_simple_context_manager_get_interfaces (manager);
        while (ifaces) {
                create_and_signal_context ((char *) ifaces->data, manager);
                g_free (ifaces->data);
                ifaces = g_list_delete_link (ifaces, ifaces);
        }

        return FALSE;
}
