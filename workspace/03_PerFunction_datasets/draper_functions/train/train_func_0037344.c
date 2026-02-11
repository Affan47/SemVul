spl_limitsort_changed(GtkComboBox *combobox, GtkWidget *spl_window) {
    Playlist *spl;
    gint index = gtk_combo_box_get_active(combobox);

    g_return_if_fail (index != -1);
    g_return_if_fail (spl_window);
    spl = g_object_get_data(G_OBJECT (spl_window), "spl_work");
    g_return_if_fail (spl);
    spl->splpref.limitsort = limitsort_comboentries[index].id;
}
