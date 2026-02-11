ario_connection_widget_musicdir_changed_cb (GtkWidget *widget,
                                            ArioConnectionWidget *connection_widget)
{
        ARIO_LOG_FUNCTION_START;
        const gchar *musicdir;


        musicdir = gtk_entry_get_text (GTK_ENTRY (connection_widget->priv->musicdir_entry));
        g_free (connection_widget->priv->current_profile->musicdir);
        if (musicdir && strcmp(musicdir, "")) {
                connection_widget->priv->current_profile->musicdir = g_strdup (musicdir);
        } else {
                connection_widget->priv->current_profile->musicdir = NULL;
        }
}
