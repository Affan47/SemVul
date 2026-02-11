renameSelectedRowCbk(GtkTreeModel* model, GtkTreePath* path,
                          GtkTreeIter* iterator, gpointer data)
{
    GtkWidget* dialog;
    GtkWidget* nameField;
    int rc;
    char* itemName;
    char* fullItemName;
    GtkWidget* warningDialog;

    gtk_tree_model_get(model, iterator, COLUMN_FILENAME, &itemName, -1);

    fullItemName = (char*)malloc(strlen(GBLisoCurrentDir) + strlen(itemName) + 1);
    if(fullItemName == NULL)
        fatalError("extractFromIsoEachRowCbk(): malloc("
                   "strlen(GBLisoCurrentDir) + strlen(itemName) + 1) failed (out of memory?)");

    strcpy(fullItemName, GBLisoCurrentDir);
    strcat(fullItemName, itemName);

    dialog = gtk_dialog_new_with_buttons(_("Enter a new name:"),
                                         GTK_WINDOW(GBLmainWindow),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_ACCEPT,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_REJECT,
                                         NULL);
    g_signal_connect(dialog, "close", G_CALLBACK(rejectDialogCbk), NULL);

    nameField = gtk_entry_new_with_max_length(NCHARS_FILE_ID_MAX_STORE);
    gtk_entry_set_text(GTK_ENTRY(nameField), itemName);
    gtk_entry_set_width_chars(GTK_ENTRY(nameField), 32);
    g_signal_connect(nameField, "activate", (GCallback)acceptDialogCbk, dialog);
    gtk_widget_show(nameField);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), nameField, TRUE, TRUE, 0);

    gtk_widget_show(dialog);

    rc = gtk_dialog_run(GTK_DIALOG(dialog));
    if(rc == GTK_RESPONSE_ACCEPT)
    {
        rc = bk_rename(&GBLvolInfo, fullItemName, gtk_entry_get_text(GTK_ENTRY(nameField)));
        if(rc < 0)
        {
            warningDialog = gtk_message_dialog_new(GTK_WINDOW(GBLmainWindow),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_CLOSE,
                                                   _("Failed to rename '%s': %s"),
                                                   itemName,
                                                   bk_get_error_string(rc));
            gtk_window_set_modal(GTK_WINDOW(warningDialog), TRUE);
            gtk_dialog_run(GTK_DIALOG(warningDialog));
            gtk_widget_destroy(warningDialog);
        }
        else
            GBLisoChangesProbable = true;
    }

    gtk_widget_destroy(dialog);

    g_free(itemName);
    free(fullItemName);
}
