setup_input_tabs (GtkBuilder    *builder,
                  CcRegionPanel *panel)
{
  GtkWidget *treeview;
  GtkTreeViewColumn *column;
  GtkCellRenderer *cell;
  GtkListStore *store;
  GtkTreeModel *filtered_store;
  GtkTreeSelection *selection;


  treeview = WID("active_input_sources");
  column = gtk_tree_view_column_new ();
  cell = gtk_cell_renderer_text_new ();
  gtk_tree_view_column_pack_start (column, cell, TRUE);
  gtk_tree_view_column_add_attribute (column, cell, "text", NAME_COLUMN);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

  store = gtk_list_store_new (N_COLUMNS,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_DESKTOP_APP_INFO);

  gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));

  input_sources_settings = g_settings_new (GNOME_DESKTOP_INPUT_SOURCES_DIR);
  g_settings_delay (input_sources_settings);
  g_object_weak_ref (G_OBJECT (builder), (GWeakNotify) g_object_unref, input_sources_settings);

  if (!xkb_info)
    xkb_info = gnome_xkb_info_new ();

#ifdef HAVE_IBUS
  ibus_init ();
  shell_name_watch_id = g_bus_watch_name (G_BUS_TYPE_SESSION,
                                          "org.gnome.Shell",
                                          G_BUS_NAME_WATCHER_FLAGS_NONE,
                                          on_shell_appeared,
                                          NULL,
                                          builder,
                                          NULL);
  g_object_weak_ref (G_OBJECT (builder), (GWeakNotify) clear_ibus, NULL);
#endif

  populate_with_active_sources (store);

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
  g_signal_connect_swapped (selection, "changed",
                            G_CALLBACK (update_button_sensitivity), builder);


  filtered_store = gtk_tree_model_filter_new (GTK_TREE_MODEL (store), NULL);
  gtk_tree_model_filter_set_visible_func (GTK_TREE_MODEL_FILTER (filtered_store),
                                          active_sources_visible_func,
                                          NULL,
                                          NULL);
  gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), filtered_store);


  g_signal_connect (WID("input_source_add"), "clicked",
                    G_CALLBACK (add_input), builder);
  g_signal_connect (WID("input_source_remove"), "clicked",
                    G_CALLBACK (remove_selected_input), builder);
  g_signal_connect (WID("input_source_move_up"), "clicked",
                    G_CALLBACK (move_selected_input_up), builder);
  g_signal_connect (WID("input_source_move_down"), "clicked",
                    G_CALLBACK (move_selected_input_down), builder);
  g_signal_connect (WID("input_source_show"), "clicked",
                    G_CALLBACK (show_selected_layout), builder);
  g_signal_connect (WID("input_source_settings"), "clicked",
                    G_CALLBACK (show_selected_settings), builder);


  update_shortcuts (builder);

  g_signal_connect (WID("jump-to-shortcuts"), "activate-link",
                    G_CALLBACK (go_to_shortcuts), panel);

  g_signal_connect (G_OBJECT (input_sources_settings),
                    "changed::" KEY_INPUT_SOURCES,
                    G_CALLBACK (input_sources_changed),
                    builder);

  g_settings_bind (input_sources_settings, "per-window",
                   WID("per-window-radio-true"), "active",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (input_sources_settings, "per-window",
                   WID("per-window-radio-false"), "active",
                   G_SETTINGS_BIND_DEFAULT | G_SETTINGS_BIND_INVERT_BOOLEAN);

  g_signal_connect_swapped (WID("per-window-radio-true"), "clicked",
                            G_CALLBACK (g_settings_apply), input_sources_settings);
  g_signal_connect_swapped (WID("per-window-radio-false"), "clicked",
                            G_CALLBACK (g_settings_apply), input_sources_settings);
}
