ario_connection_preferences_autoconnect_changed_cb (GtkWidget *widget,
                                                    ArioConnectionPreferences *connection_preferences)
{
        ARIO_LOG_FUNCTION_START;
        if (!connection_preferences->priv->loading)
                ario_conf_set_boolean (PREF_AUTOCONNECT,
                                       gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (connection_preferences->priv->autoconnect_checkbutton)));
}
