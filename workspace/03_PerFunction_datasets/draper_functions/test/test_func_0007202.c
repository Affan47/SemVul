ario_conf_get_boolean (const char *key,
                       const gboolean default_value)
{
        ARIO_LOG_FUNCTION_START;
        gchar *value = ario_conf_get (key);
        gboolean ret;

        if (!value)
                return default_value;

        ret = !strcmp (value, "1");

        return ret;
}
