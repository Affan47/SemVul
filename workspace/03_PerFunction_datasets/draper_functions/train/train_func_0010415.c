hbox_add_entry(GtkWidget *hbox, Itdb_SPLRule *splr, enum entrytype et) {
    GtkWidget *spl_window;
    GtkWidget *entry;
    gchar str[WNLEN];
    const gchar *strp;

    g_return_val_if_fail (hbox, NULL);

    str[0] = 0;

    spl_window = g_object_get_data(G_OBJECT (hbox), "spl_window");
    g_return_val_if_fail (spl_window, NULL);

    entry = gtk_entry_new();
    gtk_widget_show(entry);
    gtk_box_pack_start(GTK_BOX (hbox), entry, TRUE, TRUE, 0);
    if (et == spl_ET_STRING)
        gtk_entry_set_max_length(GTK_ENTRY (entry), ITDB_SPL_STRING_MAXLEN);
    else
        gtk_entry_set_max_length(GTK_ENTRY (entry), 50);
    strp = entry_get_string(str, splr, et);
    if (strp)
        gtk_entry_set_text(GTK_ENTRY (entry), strp);
    g_object_set_data(G_OBJECT (entry), "spl_rule", splr);
    g_object_set_data(G_OBJECT (entry), "spl_entrytype", (gpointer) et);
    g_signal_connect (entry, "changed",
            G_CALLBACK (splr_entry_changed),
            spl_window);
    g_signal_connect (entry, "activate",
            G_CALLBACK (splr_entry_redisplay),
            spl_window);
    return entry;
}
