wire_check_button(const char *preferences_key, const char *default_dir, const char *check_button_name, const char *filechooser_button_name, const char *button_clear_name) {
    GtkWidget *check_button = get_widget(check_button_name);
    GtkWidget *filechooser_button = get_widget(filechooser_button_name);
    GtkWidget *button_clear = get_widget(button_clear_name);
    g_object_set_data(G_OBJECT(check_button), FILE_CHOOSER_BUTTON_KEY, filechooser_button);
    g_object_set_data(G_OBJECT(check_button), FILE_CHOOSER_CLEAR_BUTTON_KEY, button_clear);
    g_object_set_data(G_OBJECT(button_clear), FILE_CHOOSER_BUTTON_KEY, filechooser_button);
    g_object_set_data(G_OBJECT(filechooser_button), DATA_KEY_CHECK_BUTTON, check_button);
    g_object_set_data(G_OBJECT(filechooser_button), PREFERENCES_KEY, strdup(preferences_key));
    if (default_dir != NULL)
        g_object_set_data(G_OBJECT(filechooser_button), DEFAULT_DIR_KEY, strdup(default_dir));
    g_signal_connect(check_button, "toggled", G_CALLBACK(on_media_check_button_toggled), this);
    g_signal_connect(button_clear, "clicked", G_CALLBACK(on_media_clear_button_clicked), this);
    g_signal_connect(filechooser_button, "file-set", G_CALLBACK(on_media_filechooser_file_set), this);
}
