gnc_combo_box_search_add (GtkComboBox *combo, const gchar *text, guint value)
{
    GtkListStore *store;
    GtkTreeIter iter;

    g_return_if_fail(GTK_IS_COMBO_BOX(combo));
    g_return_if_fail(text);

    store = GTK_LIST_STORE(gtk_combo_box_get_model(combo));
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       GNC_COMBO_SEARCH_COL_TEXT, text,
                       GNC_COMBO_SEARCH_COL_VALUE, value,
                       -1);
}
