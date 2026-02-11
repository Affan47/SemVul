append_introspection (GUPnPServiceProxy         *proxy,
                      GUPnPServiceIntrospection *introspection,
                      GtkTreeStore              *store,
                      GtkTreeIter               *service_iter)
{
        const GList *list;

        if (introspection == NULL) {
                gtk_tree_store_insert_with_values (store,
                                 NULL, service_iter, -1,
                                 0, get_icon_by_id (ICON_MISSING),
                                 1, _("Information not available"),
                                 5, ICON_MISSING,
                                 -1);

                return;
        }

        list = gupnp_service_introspection_list_state_variables (
                        introspection);
        if (list)
                append_state_variables (proxy,
                                        introspection,
                                        list,
                                        store,
                                        service_iter);

        list = gupnp_service_introspection_list_actions (introspection);
        if (list)
                append_actions (proxy,
                                introspection,
                                list,
                                store,
                                service_iter);
}
