plugin_configure(GtkDialog * dialog)
{
    gint i;
    GtkWidget *label, *vbox, *author_label;

    vbox = gtk_vbox_new(FALSE, 6);

    label = gtk_label_new(_("Select a pastebin:"));
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);

    author_label = gtk_label_new(_("Enter the author name:"));
    gtk_misc_set_alignment(GTK_MISC(author_label), 0, 0.5);

    widgets.author_entry = gtk_entry_new();

    if(author_name == NULL)
        author_name = g_strdup(USERNAME);

    gtk_entry_set_text(GTK_ENTRY(widgets.author_entry), author_name);

    widgets.combo = gtk_combo_box_text_new();

    for (i = 0; i < G_N_ELEMENTS(websites); i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets.combo), websites[i]);

    widgets.check_button = gtk_check_button_new_with_label(_("Show your paste in a new browser tab"));

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets.combo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), author_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets.author_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets.check_button, FALSE, FALSE, 0);

    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.combo), website_selected);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widgets.check_button), check_button_is_checked);

    gtk_widget_show_all(vbox);

    g_signal_connect(dialog, "response", G_CALLBACK(on_configure_response), NULL);

    return vbox;
}
