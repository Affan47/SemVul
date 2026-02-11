handle_config(const gchar *option_name G_GNUC_UNUSED,
                          const gchar *value,
                          gpointer data G_GNUC_UNUSED,
                          GError **error)
{
    const gchar *val;
    gchar *key;
    gsize len;

    if (!(val = strchr(value, '='))) {
        g_set_error(error, 0, 0,
                    _("Expected configuration key=value"));
        return FALSE;
    }
    len = val - value;
    val++;
    key = g_strndup(value, len);

    osinfo_entity_set_param(OSINFO_ENTITY(config),
                            key,
                            val);
    g_free(key);
    return TRUE;
}
