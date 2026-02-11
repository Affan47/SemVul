ario_browser_preferences_sync_browser (ArioBrowserPreferences *browser_preferences)
{
        ARIO_LOG_FUNCTION_START;
        GtkWidget *tree_combobox;
        int i, j;
        gchar **splited_conf;
        const gchar *conf;
        GSList *tmp;
        GtkListStore *list_store;
        GtkCellRenderer *renderer;
        GtkTreeIter iter;
        int a, b;
        gchar **items;

        gtk_combo_box_set_active (GTK_COMBO_BOX (browser_preferences->priv->sort_combobox),
                                  ario_conf_get_integer (PREF_ALBUM_SORT, PREF_ALBUM_SORT_DEFAULT));


        for (tmp = browser_preferences->priv->tree_comboboxs; tmp; tmp = g_slist_next (tmp)) {
                gtk_container_remove (GTK_CONTAINER (browser_preferences->priv->hbox), GTK_WIDGET (tmp->data));
        }
        g_slist_free (browser_preferences->priv->tree_comboboxs);
        browser_preferences->priv->tree_comboboxs = NULL;

        conf = ario_conf_get_string (PREF_BROWSER_TREES, PREF_BROWSER_TREES_DEFAULT);
        splited_conf = g_strsplit (conf, ",", MAX_TREE_NB);
        items = ario_server_get_items_names ();
        for (i = 0; splited_conf[i]; ++i) {
                tree_combobox = gtk_combo_box_new ();
                browser_preferences->priv->tree_comboboxs = g_slist_append (browser_preferences->priv->tree_comboboxs, tree_combobox);

                list_store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_INT);
                for (j = 0; j < ARIO_TAG_COUNT - 1; ++j) {
                        if (items[j]) {
                                gtk_list_store_append (list_store, &iter);
                                gtk_list_store_set (list_store, &iter,
                                                    0, gettext (items[j]),
                                                    1, j,
                                                    -1);
                        }
                }
                gtk_combo_box_set_model (GTK_COMBO_BOX (tree_combobox),
                                         GTK_TREE_MODEL (list_store));
                g_object_unref (list_store);

                renderer = gtk_cell_renderer_text_new ();
                gtk_cell_layout_clear (GTK_CELL_LAYOUT (tree_combobox));
                gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (tree_combobox), renderer, TRUE);
                gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (tree_combobox), renderer,
                                                "text", 0, NULL);

                a = atoi (splited_conf[i]);
                b = 0;
                for (j = 0; j < ARIO_TAG_COUNT - 1 && j < a; ++j) {
                        if (items[j])
                                ++b;
                }
                gtk_combo_box_set_active (GTK_COMBO_BOX (tree_combobox), b);

                g_signal_connect (G_OBJECT (tree_combobox),
                                  "changed", G_CALLBACK (ario_browser_preferences_tree_combobox_changed_cb), browser_preferences);

                gtk_box_pack_start (GTK_BOX (browser_preferences->priv->hbox), tree_combobox, TRUE, TRUE, 0);
        }
        gtk_widget_show_all (browser_preferences->priv->hbox);
        g_strfreev (splited_conf);

        gtk_spin_button_set_value (GTK_SPIN_BUTTON (browser_preferences->priv->treesnb_spinbutton), (gdouble) i);
}
