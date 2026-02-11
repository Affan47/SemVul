list_store_binding_sync_pref_to_store (ListStoreBinding *binding,
                                       GConfValue       *value)
{
        GSList *list, *l;
        GtkTreeIter iter;


        g_signal_handler_block (binding->list_store,
                                binding->row_inserted_id);
        g_signal_handler_block (binding->list_store,
                                binding->row_deleted_id);

        gtk_list_store_clear (binding->list_store);

        list = gconf_value_get_list (value);
        for (l = list; l; l = l->next) {
                GConfValue *l_value;
                const char *string;

                l_value = (GConfValue *) l->data;
                string = gconf_value_get_string (l_value);

                gtk_list_store_insert_with_values (binding->list_store,
                                                   &iter, -1,
                                                   0, string,
                                                   -1);
        }

        g_signal_handler_unblock (binding->list_store,
                                  binding->row_inserted_id);
        g_signal_handler_unblock (binding->list_store,
                                  binding->row_deleted_id);
}
