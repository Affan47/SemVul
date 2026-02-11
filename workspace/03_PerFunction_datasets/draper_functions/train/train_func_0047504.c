set_tab_preview_settings (GuPrefsGui* prefs) {

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (prefs->compile_status),
            TO_BOOL (config_get_value ("compile_status")));

    if (!config_get_value ("compile_status"))
        gtk_widget_set_sensitive (GTK_WIDGET (prefs->compile_timer), FALSE);

    gtk_spin_button_set_value (prefs->compile_timer,
                               atoi (config_get_value ("compile_timer")));

    if (STR_EQU (config_get_value ("compile_scheme"), "real_time"))
        gtk_combo_box_set_active (prefs->compile_scheme, 1);

    if (STR_EQU (config_get_value ("animated_scroll"), "always")) {
        gtk_combo_box_set_active (prefs->combo_animated_scroll, 0);
    } else if (STR_EQU (config_get_value ("animated_scroll"), "never")) {
        gtk_combo_box_set_active (prefs->combo_animated_scroll, 2);
    } else {
        gtk_combo_box_set_active (prefs->combo_animated_scroll, 1);
    }

    gtk_spin_button_set_value (prefs->spin_cache_size,
                               atoi (config_get_value ("cache_size")));
}
