cryptui_key_chooser_get_recipients (CryptUIKeyChooser *chooser)
{
    CryptUIKeyset *keyset;
    GList *recipients;
    const gchar *key;
    gchar *value;

    g_return_val_if_fail (chooser->priv->keylist != NULL, NULL);
    recipients = cryptui_key_list_get_selected_keys (chooser->priv->keylist);

    if (!chooser->priv->settings)
        return recipients;

    if (!g_settings_get_boolean (chooser->priv->settings, "encrypt-to-self"))
        return recipients;


    keyset = cryptui_key_list_get_keyset (chooser->priv->keylist);
    key = NULL;


    if (chooser->priv->keycombo)
        key = cryptui_key_combo_get_key (chooser->priv->keycombo);


    if (key == NULL) {
        value = g_settings_get_string (chooser->priv->settings, "default-key");
        if (value != NULL && value[0] != '\0')
            key = _cryptui_keyset_get_internal_keyid (keyset, value);
        g_free (value);
    }


    if (key == NULL) {
        GList *l, *keys = cryptui_keyset_get_keys (keyset);
        for (l = keys; l; l = g_list_next (l)) {
            guint flags = cryptui_keyset_key_flags (keyset, (const gchar*)l->data);
            if (flags & CRYPTUI_FLAG_CAN_SIGN && flags & CRYPTUI_FLAG_CAN_ENCRYPT) {
                key = l->data;
                break;
            }
        }
        g_list_free (keys);
    }

    if (!key)
        g_warning ("Encrypt to self is set, but no personal keys can be found");
    else
        recipients = g_list_prepend (recipients, (gpointer)key);

    return recipients;
}
