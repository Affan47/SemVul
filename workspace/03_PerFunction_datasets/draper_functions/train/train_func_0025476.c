init_track_display_preferences() {
    GtkComboBox *cmd_combo;
    gint i = 0;
    GtkWidget *w, *win;

    gchar *glade_path = g_build_filename(get_glade_dir(), "track_display.xml", NULL);
    prefbuilder = gtkpod_builder_xml_new(glade_path);
    win = gtkpod_builder_xml_get_widget(prefbuilder, "prefs_window");
    notebook = gtkpod_builder_xml_get_widget(prefbuilder, "track_settings_notebook");
    cmd_combo = GTK_COMBO_BOX(gtkpod_builder_xml_get_widget(prefbuilder, "track_exec_cmd_combo"));
    displayed_columns_view = gtkpod_builder_xml_get_widget(prefbuilder, "displayed_columns");
    ign_words_view = gtkpod_builder_xml_get_widget(prefbuilder, "ign_words_view");
    g_object_ref(notebook);
    gtk_container_remove(GTK_CONTAINER(win), notebook);
    gtk_widget_destroy(win);

    g_free(glade_path);

    setup_column_tree (GTK_TREE_VIEW(displayed_columns_view), TRUE);
    setup_ign_word_tree(GTK_TREE_VIEW(ign_words_view), TRUE);


    for (i = 0; sort_ign_fields[i] != -1; ++i) {
        gchar *buf = g_strdup_printf("sort_ign_field_%d", sort_ign_fields[i]);
        w = gtkpod_builder_xml_get_widget(prefbuilder, buf);
        g_return_val_if_fail (w, NULL);
        gtk_button_set_label(GTK_BUTTON (w), gettext (get_t_string (sort_ign_fields[i])));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (w), prefs_get_int(buf));
        g_signal_connect(w, "toggled", G_CALLBACK(on_ign_field_toggled), NULL);
        g_free(buf);
    }

    populate_track_cmd_combo(cmd_combo);

    if ((w = gtkpod_builder_xml_get_widget(prefbuilder, "horizontal_scrollbar"))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), prefs_get_int("horizontal_scrollbar"));
    }

    if ((w = gtkpod_builder_xml_get_widget(prefbuilder, "tm_cfg_case_sensitive"))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), prefs_get_int("tm_case_sensitive"));
    }

    if ((w = gtkpod_builder_xml_get_widget(prefbuilder, "tm_cfg_autostore"))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), prefs_get_int("tm_autostore"));
    }


    switch (prefs_get_int("tm_sort")) {
       case SORT_ASCENDING:
           w = gtkpod_builder_xml_get_widget(prefbuilder, "tm_sort_ascend");
           break;
       case SORT_DESCENDING:
           w = gtkpod_builder_xml_get_widget(prefbuilder, "tm_sort_descend");
           break;
       default:
           w = gtkpod_builder_xml_get_widget(prefbuilder, "tm_sort_none");
           break;
    }

    if (w)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), TRUE);

    gtk_builder_connect_signals(prefbuilder, NULL);

    return notebook;
}
