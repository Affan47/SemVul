setFileAsBootRecordCbk(GtkButton *button, gpointer data)
{
    GtkTreeSelection* selection;
    GtkWidget* dialog;

    if(!GBLisoPaneActive)

        return;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(GBLisoTreeView));

    if(gtk_tree_selection_count_selected_rows(selection) == 0)
    {
        dialog = gtk_message_dialog_new(GTK_WINDOW(GBLmainWindow),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        _("Please select a file in the ISO browser to "
                                        "use as the boot record"));
        gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if(gtk_tree_selection_count_selected_rows(selection) > 1)
    {
        dialog = gtk_message_dialog_new(GTK_WINDOW(GBLmainWindow),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        _("Please select no more than one file in the ISO browser"));
        gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    gtk_tree_selection_selected_foreach(selection, setFileAsBootRecordRowCbk, NULL);
}
