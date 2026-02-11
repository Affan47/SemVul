gconf_pk_set_default_async (const gchar    *key,
                            GFunc           callback,
                            gpointer        d,
                            GDestroyNotify  notify)
{
        GConfPKCallbackData *data;

        if (key == NULL)
                return;

        data = g_slice_new0 (GConfPKCallbackData);
        data->mandatory = FALSE;
        data->key = g_strdup (key);
        data->callback = callback;
        data->data = d;
        data->notify = notify;

        set_key_async (data);
}
