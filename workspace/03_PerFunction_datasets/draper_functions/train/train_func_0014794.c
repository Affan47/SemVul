gupnp_dlna_info_value_to_string (GUPnPDLNAInfoValue *info_value)
{
        const gchar *type;
        gchar *raw;
        gchar *str;

        g_return_val_if_fail (info_value != NULL, NULL);

        type = gupnp_dlna_value_type_name (info_value->type);
        if (info_value->unsupported)
                raw = g_strdup ("<UNSUPPORTED>");
        else
                raw = gupnp_dlna_value_type_to_string (info_value->type,
                                                       &info_value->value);
        str = g_strdup_printf ("(%s)%s", type, raw);
        g_free (raw);

        return str;
}
