select_graph_from_document(GtkButton* button, gpointer user_data)
{
    if (graph == NULL) {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "You have to choose a graphlayout file first",
            "Error"
        );
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
}
