xsettings_callback (GSettings             *settings,
                    const char            *key,
                    GnomeXSettingsManager *manager)
{
        TranslationEntry *trans;
        guint             i;
        GVariant         *value;

        if (g_str_equal (key, TEXT_SCALING_FACTOR_KEY) ||
            g_str_equal (key, SCALING_FACTOR_KEY)) {
        	xft_callback (NULL, key, manager);
        	return;
	}

        trans = find_translation_entry (settings, key);
        if (trans == NULL) {
                return;
        }

        value = g_settings_get_value (settings, key);

        process_value (manager, trans, value);

        g_variant_unref (value);

        for (i = 0; manager->priv->managers [i]; i++) {
                xsettings_manager_set_string (manager->priv->managers [i],
                                              "Net/FallbackIconTheme",
                                              "gnome");
        }
        queue_notify (manager);
}
