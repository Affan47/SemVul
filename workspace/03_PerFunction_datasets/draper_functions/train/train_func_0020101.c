keyboard_theme_new (InputPadWindowKbduiName *list)
{
    GtkTreeStore *store;
    GtkTreeIter iter;
    int i;

    g_return_val_if_fail (list != NULL, NULL);

    store = gtk_tree_store_new (THEME_N_COLS,
                                G_TYPE_INT,
                                G_TYPE_STRING, G_TYPE_STRING,
                                G_TYPE_BOOLEAN);

    gtk_tree_store_append (store, &iter, NULL);
    gtk_tree_store_set (store, &iter,
                        THEME_ID_COL, 0,
                        THEME_NAME_COL, "default",
                        THEME_DESC_COL, _("Default"),
                        THEME_VISIBLE_COL, TRUE, -1);

    for (i = 0; list[i].name; i++) {
        if (list[i].type != INPUT_PAD_WINDOW_TYPE_GTK) {
            continue;
        }
        gtk_tree_store_append (store, &iter, NULL);
        gtk_tree_store_set (store, &iter,
                            THEME_ID_COL, i + 1,
                            THEME_NAME_COL, list[i].name,
                            THEME_DESC_COL, list[i].description,
                            THEME_VISIBLE_COL, TRUE, -1);
    }
    return GTK_TREE_MODEL (store);
}
