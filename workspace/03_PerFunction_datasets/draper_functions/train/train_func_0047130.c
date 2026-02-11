on_target_format_changed(GtkComboBox *sender, gpointer e) {
    gint index = gtk_combo_box_get_active(sender);
    gchar *script = g_build_filename(get_script_dir(), conv_audio_scripts[index], NULL);
    gint i;

    for (i = 0; i < COUNTOF (modifiable_conv_paths); i++) {
        prefs_set_string(modifiable_conv_paths[i], script);
    }

    prefs_set_int("conversion_target_format", index);
    g_free(script);
    file_convert_prefs_changed();
}
