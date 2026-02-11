notify_notification_set_hint (NotifyNotification *notification,
                              const char         *key,
                              GVariant           *value)
{
        g_return_if_fail (NOTIFY_IS_NOTIFICATION (notification));
        g_return_if_fail (key != NULL && *key != '\0');

        if (value != NULL) {
                g_hash_table_insert (notification->priv->hints,
                                    g_strdup (key),
                                    g_variant_ref_sink (value));
        } else {
                g_hash_table_remove (notification->priv->hints, key);
        }
}
