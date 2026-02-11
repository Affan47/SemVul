addToIsoCbk(GtkButton *button, gpointer data)
{
    GtkTreeSelection* selection;

    if(!GBLisoPaneActive)

        return;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(GBLfsTreeView));


    GtkWidget* progressWindow;
    GtkWidget* label;


    progressWindow = gtk_dialog_new();
    gtk_dialog_set_has_separator(GTK_DIALOG(progressWindow), FALSE);
    gtk_window_set_modal(GTK_WINDOW(progressWindow), TRUE);
    gtk_window_set_title(GTK_WINDOW(progressWindow), _("Progress"));
    gtk_window_set_transient_for(GTK_WINDOW(progressWindow), GTK_WINDOW(GBLmainWindow));
    g_signal_connect_swapped(progressWindow, "delete-event",
                             G_CALLBACK(activityProgressWindowDeleteCbk), NULL);
    g_signal_connect_swapped(progressWindow, "response",
                             G_CALLBACK(cancelOperation), NULL);

    label = gtk_label_new(_("Please wait while I'm adding the selected items..."));
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(progressWindow)->vbox), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    if(GBLappSettings.scanForDuplicateFiles)
    {
        label = gtk_label_new(_("(scanning for duplicate files)"));
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(progressWindow)->vbox), label, TRUE, TRUE, 0);
        gtk_widget_show(label);
    }


    GBLactivityProgressBar = gtk_progress_bar_new();
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(progressWindow)->vbox), GBLactivityProgressBar, TRUE, TRUE, 0);
    gtk_widget_show(GBLactivityProgressBar);


    gtk_dialog_add_button(GTK_DIALOG(progressWindow), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);


    gtk_widget_show(progressWindow);


    GBLoperationCanceled = false;

    gtk_tree_selection_selected_foreach(selection, addToIsoEachRowCbk, NULL);

    gtk_widget_destroy(progressWindow);
    GBLactivityProgressBar = NULL;

    if(gtk_tree_selection_count_selected_rows(selection) > 0)

    {
        refreshIsoView();
    }


    char sizeStr[20];
    GBLisoSize = 35845;

        GBLisoSize += 2048;
    GBLisoSize += bk_estimate_iso_size(&GBLvolInfo, FNTYPE_9660 | FNTYPE_JOLIET | FNTYPE_ROCKRIDGE);
    formatSize(GBLisoSize, sizeStr, sizeof(sizeStr));
    gtk_label_set_text(GTK_LABEL(GBLisoSizeLbl), sizeStr);
}
