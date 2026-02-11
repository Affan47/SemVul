action_button_cb(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = g_object_get_data(data, "window");
    GtkWidget *chooser = g_object_get_data(data, "chooser");
    GtkWidget *toggle = g_object_get_data(data, "toggle-button");

    GSList * files = gtk_file_chooser_get_uris ((GtkFileChooser *) chooser);

    bool_t play = GPOINTER_TO_INT (g_object_get_data (data, "play-button"));
    filebrowser_add_files ((GtkFileChooser *) chooser, files, play);

    g_slist_foreach(files, (GFunc) g_free, NULL);
    g_slist_free(files);

    if (gtk_toggle_button_get_active ((GtkToggleButton *) toggle))
        gtk_widget_destroy (window);
}
