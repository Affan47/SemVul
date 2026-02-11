ipreferences_merge (IAnjutaPreferences* ipref, AnjutaPreferences* prefs,
                    GError** e)
{
    GError* error = NULL;
    ParserCxxPlugin* plugin = ANJUTA_PLUGIN_PARSER_CXX (ipref);
    plugin->bxml = gtk_builder_new ();
    GtkWidget* toggle;


    if (!gtk_builder_add_from_file (plugin->bxml, PREFS_BUILDER, &error))
    {
        g_warning ("Couldn't load builder file: %s", error->message);
        g_error_free (error);
    }
    anjuta_preferences_add_from_builder (prefs,
                                         plugin->bxml, plugin->settings,
                                         "preferences", _("Auto-complete"),
                                         ICON_FILE);
    toggle = GTK_WIDGET (gtk_builder_get_object (plugin->bxml, PREF_WIDGET_AUTO));
    g_signal_connect (toggle, "toggled", G_CALLBACK (on_autocompletion_toggled),
                      plugin);
    on_autocompletion_toggled (GTK_TOGGLE_BUTTON (toggle), plugin);
}
