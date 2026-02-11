ario_audioscrobbler_conf_username_changed_cb (guint cnxn_id,
                                              ArioAudioscrobbler *audioscrobbler)
{
        ARIO_LOG_FUNCTION_START
        const gchar *username;

        g_free (audioscrobbler->priv->username);
        audioscrobbler->priv->username = NULL;

        username = ario_conf_get_string (PREF_AUDIOSCROBBLER_USERNAME, PREF_AUDIOSCROBBLER_USERNAME_DEFAULT);
        if (username != NULL) {
                audioscrobbler->priv->username = g_strdup (username);
        }

        if (audioscrobbler->priv->username_entry) {
                char *v = audioscrobbler->priv->username;
                gtk_entry_set_text (GTK_ENTRY (audioscrobbler->priv->username_entry),
                                    v ? v : "");
        }

        audioscrobbler->priv->handshake = FALSE;
}
