list_to_string (GUPnPDLNAValueList *value_list)
{
        GList *iter;
        GPtrArray* strings = g_ptr_array_new_with_free_func (g_free);
        gchar *str;

        for (iter = value_list->values; iter != NULL; iter = iter->next) {
                GUPnPDLNAValue *value = (GUPnPDLNAValue *) iter->data;

                g_ptr_array_add (strings,
                                 gupnp_dlna_value_to_string (value,
                                                             value_list->type));
        }
        g_ptr_array_add (strings, NULL);

        str = g_strjoinv (", ", (gchar **) strings->pdata);
        g_ptr_array_unref (strings);

        return str;
}
