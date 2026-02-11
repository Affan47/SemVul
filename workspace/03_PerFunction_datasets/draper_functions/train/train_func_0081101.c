ige_conf_get_string_list (IgeConf      *conf,
                          const gchar  *key,
                          GSList      **value)
{
        IgeConfPriv *priv;
        GError      *error = NULL;

        *value = NULL;

        g_return_val_if_fail (IGE_IS_CONF (conf), FALSE);

        priv = GET_PRIVATE (conf);

        *value = gconf_client_get_list (priv->gconf_client,
                                        key,
                                        GCONF_VALUE_STRING,
                                        &error);
        if (error) {
                g_error_free (error);
                return FALSE;
        }

        return TRUE;
}
