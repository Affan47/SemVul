gdm_settings_client_get_int (const char *key,
                             int        *value)
{
        GdmSettingsEntry *entry;
        gboolean          ret;
        gboolean          res;
        char             *str;

        g_return_val_if_fail (key != NULL, FALSE);

        entry = get_entry_for_key (key);
        g_assert (entry != NULL);

        assert_signature (entry, "i");

        ret = FALSE;

        res = get_value (key, &str);

        if (! res) {

                str = g_strdup (gdm_settings_entry_get_default_value (entry));
        }

        ret = gdm_settings_parse_value_as_integer (str, value);

        g_free (str);

        return ret;
}
