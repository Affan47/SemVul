on_media_clear_button_clicked(GtkButton *button, gpointer user_data) {
    OptionsWindow *self = (OptionsWindow *)user_data;

    GtkFileChooser *filechooser = GTK_FILE_CHOOSER(g_object_get_data(G_OBJECT(button), FILE_CHOOSER_BUTTON_KEY));
    gtk_file_chooser_unselect_all(filechooser);
    const char * key = (const char *)g_object_get_data(G_OBJECT(filechooser), PREFERENCES_KEY);
    self->_current_profile->set_null_value(key);
}
